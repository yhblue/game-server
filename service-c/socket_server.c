/*
网络 IO 的核心部分代码
 */
#include "socket_server.h"
#include "socket_epoll.h"
#include "err.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>



#define MAX_EVENT 64                //epoll_wait一次最多返回64个事件
#define MAX_SOCKET 64*1024          //最多支持64k个socket连接
#define SOCKET_READBUFF 64

#define SOCKET_TYPE_INVALID 0		    // 无效的套接字
#define SOCKET_TYPE_LISTEN_NOTADD 2		// 监听套接字，未加入epoll管理
#define SOCKET_TYPE_LISTEN_ADD   3		// 监听套接字，已加入epoll管理
#define SOCKET_TYPE_CONNECT_ADD  5	    // 已连接套接，主动或被动(connect,accept成功，并已加入epoll管理)
#define SOCKET_TYPE_HALFCLOSE  6	    // 应用层已发起关闭套接字请求，应用层发送缓冲区尚未发送完，未调用close
#define SOCKET_TYPE_CONNECT_NOTADD 7		// accept返回的已连接套接字，但未加入epoll管理
#define SOCKET_TYPE_OTHER          8		// 其它类型的文件描述符，比如stdin,stdout等

struct append_buffer
{
	struct append_buffer* next;
	void* buffer;//in order to free memery
	void* current;
	int size;   //这块缓冲区中剩余未发送的字节数
};

struct socket
{
	int fd;       //socket fd  
	int id;       //id
	int type;     //socket type
	int remain_size; //缓冲区链表剩余的字节数
	struct append_buffer* head;
	struct append_buffer* tail;
};

struct socket_server 
{
    int epoll_fd;                //epoll fd
    int event_n;                 //epoll_wait return number of event
    struct socket* socket_pool;  //socket pool，record every socket massage
    struct event* event_pool;    //event pool,record event massage
    int event_index;             //from 0 to 63
};

struct request_close 
{
	int id;
};

struct request_send
{
	int id;
	int size;
	char * buffer;
};

struct request_package
{
	uint8_t header[8];//header[0]->massage type header[1]->massage len
	union
	{
		char buffer[256];
		//struct request_open open;
		struct request_send send;
		struct request_close close;	
	}msg;
};

//---------------------------------------------------------------------------------------------------------------------------

static int append_remaindata(struct socket *s,struct request_send * request,int start)
{
	struct append_buffer* node = (struct append_buffer*)malloc(sizeof(struct append_buffer));
	if(node == NULL)
		return -1;
	node->current = request->buffer + start;
	node->size = request->size - start;
	node->buffer = request->buffer;
	node->next = NULL;
	s->remain_size += node->size;
	if(s->head == NULL)
	{
		s->head = s->tail = node;
	}
	else
	{
		s->tail->next = node;
		s->tail = node;
	}
	return 0;
}


//id from 1-2^31-1
static int apply_id()
{
	static int id = 0;
	id ++;
	if(id < 0) 
	{
		id = 1;
	}
	return id;
}

//apply a socket from socket_pool 
static struct socket* apply_socket(struct socket_server *ss,int fd,int id,bool add_epoll)
{
	struct socket* s = &ss->socket_pool[id % MAX_SOCKET];
	if(s == NULL)
	{
	 	return NULL;
	}

	assert(s->type == SOCKET_TYPE_INVALID);

	if(add_epoll)
	{
		if(epoll_add(ss->epoll_fd,fd,s) == -1)
		{
			s->type = SOCKET_TYPE_INVALID;
			return NULL;
		}
	}

	s->fd = fd;
	s->id = id;
	return s;
}

static void socket_keepalive(int fd)
{
	int keep_alive = 1;
	setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,(void*)&keep_alive,sizeof(keep_alive));
}


static int do_listen(const char* host,int port,int max_connect)
{
    int  listen_fd;
    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if (listen_fd == -1)
    {
        fprintf(ERR_FILE,"listen socket create error\n");
        return -1;
    }

    struct sockaddr_in serv_addr;     //ipv4 struction
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  //ipv4
    serv_addr.sin_addr.s_addr = inet_addr(host);
    serv_addr.sin_port = htons(port);              //主机->网络

    int optval = 1;
    if(setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) == -1)
    {
    	fprintf(ERR_FILE,"setsockopt failed\n");  
    	goto _err;   
    }
    if (bind(listen_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        fprintf(ERR_FILE,"bind failed\n");  
        goto _err;      
    }
	if (listen(listen_fd, max_connect) == -1) 
	{
		fprintf(ERR_FILE,"listen failed\n"); 
		goto _err;
	}    
    return listen_fd;

_err:
	close(listen_fd);
	return -1;  
}

//为 listen_fd 申请 socket_pool 中一个成员
static int listen_socket(struct socket_server *ss,int listen_fd,int id)
{
	struct socket *s = apply_socket(ss,listen_fd,id,false);
	if(s == NULL)
	{
		fprintf(ERR_FILE,"listen_id apply socket failed\n"); 
		goto _err;
	}  
	s->type = SOCKET_TYPE_LISTEN_NOTADD;//未放入 epoll 中管理
	return 0;
_err:
	close(listen_fd);
	ss->socket_pool[id % MAX_SOCKET].type = SOCKET_TYPE_INVALID; //return to pool
	return -1;
}

static int dispose_accept(struct socket_server *ss,struct socket *s,struct socket_message *result)
{
	int listen_fd = s->fd;
	struct sockaddr_in address;
	socklen_t addr_len = sizeof(address);
	int client_fd = accept(listen_fd,(struct sockaddr*)&address,(socklen_t*)&addr_len);
	if(client_fd == -1)
	{
		fprintf(ERR_FILE,"accept failed\n");
		return -1;
	}

	int id = apply_id();
	socket_keepalive(client_fd);
	if(set_nonblock(client_fd) == -1)
	{
		fprintf(ERR_FILE,"set set_nonblock failed\n");
		return -1;
	}
	struct socket* cs = apply_socket(ss,client_fd,id,false);
	if(cs == NULL) //
	{
		close(client_fd);
		fprintf(ERR_FILE,"apply socket from pool failed\n");
		return -1;
	}
	cs->type = SOCKET_TYPE_CONNECT_NOTADD;
	result->id = id;
	result->lid_size = s->id;//listen_id
	result->data = "accept new client";
	return 0;   
}

//这个函数要修改，增加内存泄露管理
static void close_fd(struct socket_server *ss,struct socket *s,struct socket_message * result)
{
	if(s->type == SOCKET_TYPE_INVALID)
	{
		return;
	}
	if(s->type!=SOCKET_TYPE_LISTEN_NOTADD || s->type!=SOCKET_TYPE_CONNECT_NOTADD)
	{
		if(epoll_del(ss->epoll_fd,s->fd) == -1)
		{
			fprintf(ERR_FILE,"epoll_del failed s->fd=%d\n",s->fd);
		}
	}
	result->id = s->id;
	result->data = "close";

	s->id = 0;
	close(s->fd);
	s->type = SOCKET_TYPE_INVALID;
}

//处理epoll的可读事件
static int dispose_readmessage(struct socket_server *ss,struct socket *s, struct socket_message * result)
{
	int size = SOCKET_READBUFF;
	char* buffer = (char*)malloc(size);
	memset(buffer,0,size);
	int n = (int)read(s->fd,buffer,size);
	if(n < 0)
	{
		free(buffer);
		switch(errno)
		{
			case EINTR:
				fprintf(ERR_FILE,"socket read,EINTR\n");
				break;    // wait for next time
			case EAGAIN:
				fprintf(ERR_FILE,"socket read, EAGAIN\n");
				break;
			default:
				close_fd(ss,s,result);
				return SOCKET_ERROR;			
		}
		return -1;
	}
	if(n == 0) //client close,important
	{
		free(buffer);
		close_fd(ss,s,result);
		return SOCKET_CLOSE;
	}

	result->id = s->id;
	result->lid_size = n;
	result->data = buffer;
	return SOCKET_DATA;
}

static int send_data(struct socket_server* ss,struct socket *s,struct socket_message *result)
{
	while(s->head)
	{
		struct append_buffer * tmp = s->head;
		for( ; ; )
		{
			int n = write(s->fd,tmp->current,tmp->size);
			if(n == -1)
			{
				switch(errno)
				{
					case EINTR:
						continue;
					case EAGAIN:
						return -1;
					default:
					fprintf(stderr, "send_data: write to %d (fd=%d) error.",s->id,s->fd);
					close_fd(ss,s,result);
					return -1;
				}
			}
			s->remain_size -= n;
			if(n != tmp->size)   //未完全发送完
			{
				tmp->current += n;
				tmp->size -= n; 
			}
			if(n == tmp->size)
			{
				s->head = tmp->next;
				if(tmp->buffer != NULL)
				{
					free(tmp->buffer);
					free(tmp); //last s->head node 
				}
			}
		}
	}	
	s->tail = NULL;
	epoll_write(ss->epoll_fd,s->fd,s,false);  //写完了，取消关注写事件
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
struct socket_server* socket_server_create()
{
	int efd = epoll_init();
	if(efd_err(efd))
	{
		fprintf(ERR_FILE,"epoll create failed\n");
		return NULL;
	}

	struct socket_server *ss = malloc(sizeof(*ss));
	ss->epoll_fd = efd;
	ss->event_n = 0;
	ss->socket_pool = (struct socket*)malloc(sizeof(struct socket)*MAX_SOCKET);
	if(ss->socket_pool == NULL)
	{
		fprintf(ERR_FILE,"socket_pool malloc failed\n");
	}
	ss->event_pool = (struct event*)malloc(sizeof(struct event)*MAX_EVENT);
	if(ss->event_pool == NULL)
	{
		fprintf(ERR_FILE,"event_pool malloc failed\n");
		return NULL;
	}
	ss->event_index = 0;

	int i = 0;
	struct socket *s = NULL;
	for(i=0; i<MAX_SOCKET; i++)
	{
		s = &ss->socket_pool[i];
		s->fd = 0;
		s->id = 0;
		s->type = SOCKET_TYPE_INVALID;
		s->remain_size = 0;
		s->head = NULL;
		s->tail = NULL;
	}
	return ss;
}


int socket_server_listen(struct socket_server *ss,const char* host,int port,int backlog)
{
	int listen_fd = do_listen(host,port,backlog);
	if(listen_fd == -1)
	{
	   return -1;
	}
	printf("listen_fd = %d\n",listen_fd);
	int id = apply_id();
	if(listen_socket(ss,listen_fd,id) == 0)
	{
		return id;
	}
	return -1;
}

int socket_server_event(struct socket_server *ss, struct socket_message * result)
{
	for( ; ; )
	{
//		printf("test\n");
		if(ss->event_index == ss->event_n)  //all event was done,call sepoll_wait again
		{
//			printf("start sepoll_wait function!\n");
			ss->event_n = sepoll_wait(ss->epoll_fd,ss->event_pool,MAX_EVENT);
			if(ss->event_n <= 0) //err
			{
				ss->event_n = 0;
				return -1;
			}	
			ss->event_index = 0;
//			printf("end sepoll_wait dispath! ss->event_n = %d\n",ss->event_n);
		}
		struct event* eve = &ss->event_pool[ss->event_index++];
		struct socket *s = eve->s_p; //指向了产生可读事件的fd注册到epoll时候分配的socket_pool中成员
		// printf("s->type = %d\n",s->type);
		// printf("s->fd = %d\n",s->fd);
		// printf("s->id = %d\n",s->id);
		switch(s->type) //判断哪一类型的socket发生变化
		{
			case SOCKET_TYPE_LISTEN_ADD: //client connect
				if(dispose_accept(ss,s,result) == 0)
				{
					return SOCKET_ACCEPT;			
				}
				break;
			case SOCKET_TYPE_INVALID:
				fprintf(ERR_FILE,"a invalied socket from pool\n");
				break;
			case SOCKET_TYPE_CONNECT_ADD:
				if(eve->read)
				{
					int ret_type = dispose_readmessage(ss,s,result);
					if(ret_type == -1)
					{
						break; 
					}
					return ret_type;
				}
				if(eve->write)
				{
					send_data(ss,s,result);
				}
				if(eve->error)
				{
					;
				}
				break;
		}
	}
}


int socket_server_start(struct socket_server *ss,int id)
{
	struct socket *s = &ss->socket_pool[id % MAX_SOCKET];  
	if(s == NULL)
	{
		return SOCKET_ERROR;
	}
	if(s->type == SOCKET_TYPE_INVALID) //
	{
		return SOCKET_ERROR;
	}
	if (s->type == SOCKET_TYPE_CONNECT_NOTADD || s->type == SOCKET_TYPE_LISTEN_NOTADD) 
	{
//		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//		printf("socket_server_start s->type = %d\n",s->type);
		if(epoll_add(ss->epoll_fd,s->fd,s) == -1)
		{
			s->type = SOCKET_TYPE_INVALID;
			return SOCKET_ERROR;
		}
		s->type = (s->type == SOCKET_TYPE_CONNECT_NOTADD) ? SOCKET_TYPE_CONNECT_ADD : SOCKET_TYPE_LISTEN_ADD;//change
//		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		return SOCKET_SUCCESS;//成功加入到 epoll 中管理。
	}
	return SOCKET_ERROR;
}


void socket_server_release(struct socket_server *ss)
{
	int i = 0;
	struct socket *s = NULL;
	for(i=0; i<MAX_SOCKET; i++)
	{
		s = &ss->socket_pool[i];
		if(s->type == SOCKET_TYPE_CONNECT_ADD || s->type == SOCKET_TYPE_LISTEN_ADD)
		{
			epoll_del(ss->epoll_fd,s->fd);
		}
		close(s->fd);
	}
	epoll_release(ss->epoll_fd);	
	free(ss->socket_pool);
	free(ss->event_pool);
	free(ss);
}


//管道中接收到其他进程发过了的写socket操作调用。
int socket_server_send(struct socket_server* ss,struct request_send * request,struct socket_message *result)
{
	int id = request->id;
	struct socket * s = &ss->socket_pool[id % MAX_SOCKET];
	if(s->type != SOCKET_TYPE_CONNECT_ADD) //加入管道通信功能后这里可能要修改
	{
		if(request->buffer != NULL)
		{
			free(request->buffer);
			request->buffer = NULL;			
		}
		return -1;
	}
	if(s->head == NULL)
	{
		int n = write(s->fd,request->buffer,request->size);
		if(n == -1)
		{
			switch(errno)
			{
				case EINTR:
				case EAGAIN:
					n = 0;
					break;
				default:
					fprintf(stderr, "socket_server_send: write to %d (fd=%d) error.",id,s->fd);
					close_fd(ss,s,result);
					if(request->buffer != NULL)
					{
						free(request->buffer);
						request->buffer = NULL;
					}
					return -1;
			}
		}
		if(n == request->size)
		{
			if(request->buffer != NULL)
			{
				free(request->buffer);
				request->buffer = NULL;
			}		
			return 0;
		}
		if(n < request->size)
		{
			append_remaindata(s,request,n);  //
			epoll_write(ss->epoll_fd,s->fd,s,true);
		}		
	}
	else
	{
		append_remaindata(s,request,0);
	}
	return 0;
}


void read_test(struct socket_server* ss,int id,const char* data,int size,struct socket_message *result)
{
	struct request_send * request = (struct request_send*)malloc(sizeof(struct request_send));
	request -> id = id;
	request->size = size;
	request->buffer = (char*)data;

	socket_server_send(ss,request,result);
}