#include "socket_server.h"

void main()
{
	struct socket_server* ss = socket_server_create();
	if(ss == NULL)
		return -1;
	int pipe_fd = ss->pipe_write_fd; //logic进程->网络进程

	pid = fork();
	if(pid >0) //网络进程
	{
		int listen_id = socket_server_listen(ss,"127.0.0.1",8888,32);
		printf("listen_id = %d\n",listen_id);
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
					
				case SOCKET_ACCEPT://client connect
					printf("accept[id=%d] from [id=%d]",result.id,result.lid_size);
					socket_server_start(ss,result.id);  //add to epoll

				case SOCKET_DATA:
				case SOCKET_CLOSE:
				case SOCKET_SUCCESS:
					break;

				default:
					break;	
			}
		}
	_EXIT:
		socket_server_release(ss);			
	}
}


				// case SOCKET_DATA:
				// 	printf("data[id=%d],size=%d,%s\n",result.id,result.lid_size,result.data);
				// 	//free(result.data);
				// 	//read_test(ss,result.id,result.data,result.lid_size,&result);
				// 	//这里变成把数据发送到网关的逻辑处理线程
				// 	//
				// 	break;
				// case SOCKET_ACCEPT://client connect
				// 	printf("accept[id=%d] from [id=%d]",result.id,result.lid_size);
				// 	socket_server_start(ss,result.id);  //add to epoll
				// 	break;		
				// case SOCKET_CLOSE:
				// 	printf("closed[id=%d]\n",result.id);
				// 	break;
				// case SOCKET_SUCCESS:	
				// 	printf("success[id=%d] add to epoll\n",result.id);
				// 	break;
