#include "socket_server.h"
#include "socket_epoll.h"

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

		switch(type)
		{
			case SOCKET_EXIT:
				goto _EXIT;
			case SOCKET_DATA:
				printf("data(%lu) [id=%d] %s\n", result.opaque, result.id, result.data);
				break;
			case SOCKET_ACCEPT:
				printf("accept[id=%d]",);
				break;
			
		}
	}
_EXIT:

}


/*
//@ssize_t：返回读的长度 若ssize_t<count 读失败失败
//@buf：接受数据内存首地址
//@count：接受数据长度
ssize_t readn(int fd, void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nread;
	char *bufp = (char*)buf;

	while (nleft > 0)
	{
		if ((nread = read(fd, bufp, nleft)) < 0)
		{	
			if (errno == EINTR)
				continue;
			return -1;
		}
		else if (nread == 0) //若对方已关闭
			return count - nleft;

		bufp += nread;
		nleft -= nread;
	}

	return count;
}

//1一次全部读走 //2次读完数据 //出错分析 //对方已关闭
//思想：tcpip是流协议，不能1次把指定长度数据，全部写完 
//按照count大小写数据
//若读取的长度ssize_t<count 说明读到了一个结束符，对方已关闭。
//@ssize_t：返回写的长度 -1失败
//@buf：待写数据首地址
//@count：待写长度

ssize_t writen(int fd, const void *buf, size_t count)
{
	size_t nleft = count;
	ssize_t nwritten;
	char *bufp = (char*)buf;

	while (nleft > 0)
	{
		if ((nwritten = write(fd, bufp, nleft)) < 0)
		{
			if (errno == EINTR)
				continue;
			return -1;
		}
		else if (nwritten == 0)
			continue;

		bufp += nwritten;
		nleft -= nwritten;
	}

	return count;
}
*/