#ifndef poll_socket_epoll_h
#define poll_socket_epoll_h

#include <sys/epoll.h>
#include <stdbool.h>

struct event {
	void * s_p; //指向注册到epoll时候对应的socket_pool的成员
	bool read;
	bool write;
};

int epoll_init();
int efd_err(int efd);
int epoll_release(int efd);
int epoll_add(int efd, int sock, void *ud);
int epoll_del(int efd,int sock);
int sepoll_wait(int efd, struct event *e, int max);
int set_nonblock(int fd);
#endif
