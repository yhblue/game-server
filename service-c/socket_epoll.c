#include "socket_epoll.h"
#include <sys/epoll.h>


int socket_epoll_init()
{
    return epoll_create(1024);
}

int socket_epoll_add(int efd, int sock, void *ud)
{
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = ud;

	if (epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev) == -1) 
	{
		return 1;
	}
	return 0;
}


void socket_epoll_del(int efd,int sock)
{
   epoll_ctl(efd, EPOLL_CTL_DEL, sock , NULL);
}

void 