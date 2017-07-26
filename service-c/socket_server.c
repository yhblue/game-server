/*
网络 IO 的核心部分代码
 */
#include "socket_server.h"
#include "socket_epoll.h"
#include "err.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define MAX_EVENT 64    //epoll_wait一次最多返回64个事件
#define MAX_SOCKET 64*1024  //最多支持64k个socket连接
struct event
{
	void * ptr;        
	bool read_event;
	bool write_event;
};

struct socket
{
	int fd;
	int id;
	int type;     //socket type
};

struct socket_server 
{
    poll_fd epoll_fd;            //epoll fd
    int event_n;                 //epoll_wait返回的事件个数
    struct socket* socket_pool;  //socket pool，record every socket massage
    struct event* event_pool;    //event pool,record event massage
    int event_index;             //from 0 to 63
};


struct socket_server* socket_server_create()
{
	poll_fd efd = epoll_init();
	if(efd_err(efd))
	{
		fprintf(ERR_FILE, "epoll create failed%s\n");
		return NULL;
	}

	struct socket_server *ss = malloc(sizeof(*ss));
	ss->epoll_fd = efd;
	ss->event_n = 0;
	ss->socket_pool = (struct socket*)malloc(sizeof(struct socket)*MAX_SOCKET);
	ss->event_pool = (struct)malloc(sizeof(struct event)*MAX_EVENT);
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

    struct sockaddr_in servaddr;     //ipv4 struction
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;  //ipv4
    srvaddr.sin_addr.s_addr = inet_addr(host);
 //   inet_pton(AF_INET,host,&servaddr.sin_addr); //字符串->网络字节流  
    servaddr.sin_port = htons(port);              //主机->网络

    int optval = 1;
    if(setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval)) == -1)
    {
    	fprintf(ERR_FILE,"setsockopt failed\n");  
    }
    if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
        fprintf(ERR_FILE,"bind failed\n");  
        goto _err;      
    }
	if (listen(listen_fd, backlog) == -1) 
	{
		fprintf(ERR_FILE,"listen failed\n"); 
		goto _err;
	}    
    return listenfd;

_err:
	close(listenfd);
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
    
}





