#ifndef poll_socket_epoll_h
#define poll_socket_epoll_h

#include <sys/epoll.h>
#include <stdbool.h>

struct event {
	void * s;
	bool read;
	bool write;
};

int epoll_init();
int efd_err(int efd);
int epoll_release(int efd);
int epoll_add(int efd, int sock, void *ud);
void epoll_del(int efd,int sock);
int sepoll_wait(int efd, struct event *e, int max);

#endif
