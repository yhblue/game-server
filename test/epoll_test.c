#include "socket_server.h"
#include "socket_epoll.h"

int main()
{
	struct socket_server* ss = socket_server_create();
	int listen_fd = socket_server_listen();

}