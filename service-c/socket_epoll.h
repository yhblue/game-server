#ifndef poll_socket_epoll_h
#define poll_socket_epoll_h

int epoll_init();
int efd_err(int efd);
void epoll_release(int efd);
int epoll_add(int efd, int sock, void *ud);
void epoll_del(int efd,int sock);
void epoll_wait(int efd, struct event *e, int max);

#endif
