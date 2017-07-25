#include "socket_epoll.h"
#include <sys/epoll.h>


int epoll_init()
{
   int efd = epoll_create(1024);
}

int efd_err(int efd)
{
	return efd ==-1;
}
void epoll_release(int efd)
{
     close(efd);
}

int epoll_add(int efd, int sock, void *ud)
{
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = ud;

	if (epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev) == -1) 
	{
		return -1;
	}
	return 0;
}

void epoll_del(int efd,int sock)
{
   epoll_ctl(efd, EPOLL_CTL_DEL, sock , NULL);
}

void epoll_wait(int efd, struct event *e, int max)
{
    struct epoll_event ev[max];
    int ret_n = epoll_wait(efd,ev,max,-1);  //-1没有句柄发生变化，则一直等待
    
}

