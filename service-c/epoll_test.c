#include "socket_server.h"
#include "socket_epoll.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	struct socket_server* ss = socket_server_create();
	if(ss == NULL)
		return -1;

	int listen_id = socket_server_listen(ss,"127.0.0.1",8888,32);
	if(listen_id == -1)
		return -1;
	socket_server_start(ss,listen_id);
	
	struct socket_message result;
	for ( ; ; )
	{
		int type = socket_server_event(ss,&result);

		switch(type)  //这里以后代替为与框架数据处理进程通信的代码
		{
			case SOCKET_EXIT:
				goto _EXIT;
			case SOCKET_DATA:
				printf("data[id=%d],size=%d,%s\n",result.id,result.lid_size,result.data);
				free(result.data);
				break;
			case SOCKET_ACCEPT://client connect
				printf("accept[id=%d] from [id=%d]",result.id,result.lid_size);
				socket_server_start(ss,result.id);  //add to epoll
				break;		
			case SOCKET_CLOSE:
				printf("closed[id=%d]",result.id);
				break;
			case SOCKET_SUCCESS:	
				printf("success[id=%d] add to epoll\n",result.id);
				break;
		}
	}
_EXIT:
	socket_server_release(ss);
}