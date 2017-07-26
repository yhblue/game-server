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


#define MAX_EVENT 64         //epoll_wait一次最多返回64个事件
#define MAX_SOCKET 64*1024  //最多支持64k个socket连接

#define SOCKET_TYPE_INVALID 0		// 无效的套接字
#define SOCKET_TYPE_RESERVE 1		// 预留，已被申请，即将投入使用
#define SOCKET_TYPE_PLISTEN 2		// 监听套接字，未加入epoll管理
#define SOCKET_TYPE_LISTEN 3		// 监听套接字，已加入epoll管理
#define SOCKET_TYPE_CONNECTING 4	// 尝试连接中的套接字
#define SOCKET_TYPE_CONNECTED 5		// 已连接套接，主动或被动(connect,accept成功，并已加入epoll管理)
#define SOCKET_TYPE_HALFCLOSE 6		// 应用层已发起关闭套接字请求，应用层发送缓冲区尚未发送完，未调用close
#define SOCKET_TYPE_PACCEPT 7		// accept返回的已连接套接字，但未加入epoll管理
#define SOCKET_TYPE_OTHER 8			// 其它类型的文件描述符，比如stdin,stdout等

struct socket
{
	int fd;
	int id;
	int type;     //socket type
};

struct socket_server 
{
    int epoll_fd;                //epoll fd
    int event_n;                 //epoll_wait返回的事件个数
    struct socket* socket_pool;  //socket pool，record every socket massage
    struct event* event_pool;    //event pool,record event massage
    int event_index;             //from 0 to 63
};

struct request_star
{
	int id;
};

struct request_close 
{
	int id;
};

struct request_send
{
	int id;
	int sz;
	char * buffer;
};

struct request_package
{
	uint8_t header[8];//header[0]->massage type header[1]->massage len
	union _msg
	{
		char buffer[256];
		//struct request_open open;
		struct request_send send;
		struct request_star start;
		struct request_close close;	
	}msg;
};

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
	ss->event_pool = (struct event*)malloc(sizeof(struct event)*MAX_EVENT);
	if((!ss->socket_pool) || (!ss->event_pool))
	{
		fprintf(ERR_FILE,"socket_pool or event_pool malloc failed");
		return NULL;
	}
	ss->event_index = 0;

	int i = 0;
	for(i=0; i<MAX_SOCKET; i++)
	{
		struct socket *s = &ss->socket_pool[i];
		s->fd = 0;
		s->id = 0;
	}

}

static int do_listen(const char* host,int port,int backlog)
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
 //   inet_pton(AF_INET,host,&servaddr.sin_addr); //字符串->网络字节流  
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
	if (listen(listen_fd, backlog) == -1) 
	{
		fprintf(ERR_FILE,"listen failed\n"); 
		goto _err;
	}    
    return listen_fd;

_err:
	close(listen_fd);
	return -1;  
}

int socket_server_listen(struct socket_server *ss,const char* host,int port,int backlog)
{
	int fd = do_listen(host,port,backlog);
	if(fd < 0)
	{
	   return -1;
	}
}

int socket_server_event(struct socket_server *ss, struct socket_message * result)
{
    ss->event_n = sepoll_wait(ss->epoll_fd,);
}

//id from 0-2^31-1
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

//fd->epoll
void socket_server_start(struct socket_server *ss,int id)
{
	struct request_package request;
	request.msg.start.id = id;
}

//client fd->epoll 
static int start_socket(struct socket_server *ss,struct request_start* reques,struct socket_message* result)
{
	int id = reques.msg.start.id; 
	result.id = fd;
	result->ud = 0;
	result->data = NULL;
	struct socket *s = ss->socket_pool[id % MAX_SOCKET];  
	if(s->type == SOCKET_TYPE_INVALID || s->id = !id) //
	{
		return SOCKET_ERROR;
	}
	if (s->type == SOCKET_TYPE_PACCEPT || s->type == SOCKET_TYPE_PLISTEN) 
	{
		if(epoll_add(ss->epoll_fd,s->fd,s->fd,s) == -1)
		{
			s->type = SOCKET_TYPE_INVALID;
			return SOCKET_ERROR;
		}
		s->type = (s->type == SOCKET_TYPE_PACCEPT) ? SOCKET_TYPE_CONNECTED : SOCKET_TYPE_LISTEN;//change
		result->data = "start";
		return SOCKET_SUCCESS;
	}
}

