//实现功能:
//1)解析 protobuf 协议,转发到相应的游戏逻辑进程
//2)对游戏逻辑进程要发送的数据使用 protobuf 系列化，通知网络发送线程发送

#include "net_logic.h"
#include "message.pb-c.h"
#include "lock_queue.h"
#include "err.h"
#include "socket_epoll.h"

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

#define NET_LOGIC_MAX_EVENT  10
#define GAME_PROCESS_NUM      4

#define EVENT_TYPE_QUE_NULL  1

#define PROCESS_TYPE_NET_IO       1
#define PROCESS_TYPE_GAME_LOGIC   2

typedef struct _upack_buf
{
	int uid;
	char msg_type;   //通知游戏逻辑进程这个消息是哪种类型
	char data_type;  //当消息类型为客户端数据时候，记录使用的数据结构类型
	char *buffer; 	//客户端发过来的经过反序列化之后的原始数据

}upack_buf;

typedef struct _process
{
	int p_id;
	int sock_fd;
	int type;
}process;

typedef struct _net_logic
{
	queue* que;
	int epoll_fd;
	int game_socket_fd[];
	int sock_id_2_game_fd[];
	int online_player[]; 		//下标是一个地图编号，对应的值是这一块地图上的玩家人数
	struct event* event_pool;
	process* game_process_pool; 
	bool check_que;
	int event_index;
	int event_n;
}net_logic;


static upack_buf* unpack_user_data(char* data_pack,int len)
{
	char type = data_pack[0]; //
	char *seria_data = data_pack+1;
	upack_buf* upack_data = NULL;

	switch(type)
	{
		case LOG_REQ:
			break;
		case HERO_MSG_REQ:
			break;
		case CONNECT_REQ:
			break;
		case HEART_REQ:
			break;
	}
	return upack_data;
}

static int apply_process_id()
{
	static int id = -1;
	id ++;
	return id;	
}

static process* apply_process(net_logic* nt,int socket_fd,int p_id,bool add_epoll)
{
	process* g_p = &nt->game_process_pool[p_id % GAME_PROCESS_NUM];
	if(g_p == NULL)
	{
		return NULL;
	}
	if(add_epoll)
	{
		if(epoll_add(nt->epoll_fd,socket_fd,g_p) == -1)
		{
			return NULL;
		}
	}	
	g_p->p_id = p_id;
	g_p->sock_fd = socket_fd;
}

static void close_proces_fd()
{

}

int connect_game_logic()
{

}
//------------------------------------------------------------------------------------------------------------------------
static int dispose_queue_event(net_logic* nl)
{
	queue* que = nl->que;
	q_node* qnode = queue_pop(que);
	if(qnode == NULL) //队列无数据
	{
		return -1;
	}
	else
	{
		char type = qnode->type;
		int uid = qnode->uid;
		char* data = qnode->buffer;
		int len = qnode->len;
		upack_buf* send_data = NULL;
		switch(type)
		{
			case TYPE_DATA://数据包--解析
			send_data = unpack_user_data(data,len);
			//发送
			break;

			case TYPE_CLOSE:
			case TYPE_SUCCESS:
			break;
		}		
	}
	return 0;
}

//发送完成之后记得释放内存
int send_data_2_game_logic(char* data,int len)
{

}

//写一个函数，能够根据传递过来的socket的id知道它现在在哪个游戏逻辑进程
//得到该进程的连接上来的 socket fd
int get_game_logic_id(int socket_id)
{

}


net_logic* net_logic_creat()
{
	net_logic *nt = (net_logic*)malloc(sizeof(struct net_logic));
	if(nt == NULL)
		return -1;
	int efd = epoll_init();
	if(efd_err(efd))
	{
		fprintf(ERR_FILE,"net_logic_creat:epoll create failed\n");
		return NULL;
	}
	nt->epoll_fd = efd;

	int size = sizeof(struct event) * NET_LOGIC_MAX_EVENT;
	nt->event_pool = (struct event*)malloc(size);
	if(nt->event_pool == NULL)
	{
		fprintf(ERR_FILE,"net_logic_creat:event_pool malloc failed\n");
		epoll_release(efd);
		return NULL;	
	}
	memset(nt->event_pool,0,size);
	size = sizeof(process) * GAME_PROCESS_NUM;
	nt->game_process_pool = (process*)malloc(size);
	if (nt->game_process_pool == NULL)
	{
		fprintf(ERR_FILE,"net_logic_creat:event_pool malloc failed\n");
		epoll_release(efd);
		free(nt->event_pool);
		return NULL;		
	}
	for(int i=0; i<GAME_PROCESS_NUM; i++)
	{
		process* gp = &nt->game_process_pool[i % GAME_PROCESS_NUM];
		gp->p_id = 0;
		gp->sock_fd = 0;
		gp->type = 0;
	}
	nt->check_que = false;
	nt->nt->event_index = 0;
	nt->event_n = 0;
	return nt;
}



void* net_logic_event_thread(void* arg)
{
	net_logic *nt = net_logic_creat();
	if(nt == NULL)
		return -1;	
	nt->que = arg;

}


int net_logic_event(net_logic *nt)
{
	for( ; ; )
	{
		if(nt->check_que == true)
		{
			int ret = dispose_queue_event(nt);
			if(ret == -1) //queue is null
			{
				nt->check_que = false;
				return EVENT_TYPE_QUE_NULL;
			}
			else
			{
				continue;
			}
		}
		if(nt->event_index = nt->event_n)
		{
			nt->event_n = sepoll_wait(nt->epoll_fd,nt->event_pool,NET_LOGIC_MAX_EVENT);
			if(nt->event_n <= 0) //error
			{
				fprintf(ERR_FILE,"net_logic_event:sepoll_wait return error event_n\n");
				ss->event_n = 0;
				return -1;
			}	
			nt->event_index = 0;
		}
		ss->event_index = 0;			
		struct event* eve = &nt->event_pool[ss->event_index++];  //read or write
		process* g_p = eve->s_p; 			                 //which process socket

		switch(g_p->type)
		{
			case PROCESS_TYPE_NET_IO:
				nt->check_que = true;
				break;

			case PROCESS_TYPE_GAME_LOGIC:
				break;
		}

	}
}


//有新的游戏逻辑进程连接上来就调用该函数
//把游戏逻辑进程的 socket 加入到 epoll 中管理
int proces_socket_start(net_logic *nt,int sock_fd)
{
	int p_id = apply_process_id();

	struct socket* cs = apply_process(nt,sock_fd,p_id,true);
	if(cs == NULL) 
	{
		close(sock_fd); //err close
		fprintf(ERR_FILE,"proces_socket_start: apply_process failed\n");
		return -1;
	}
	return 0;
}



//传递过来的数据第一个字节是 protobuf 消息的类型
//需要与客户端的约定一致
int pack_user_data()
{

}








