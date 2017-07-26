#ifndef  _SOCKET_SERVER_H
#define _SOCKET_SERVER_H

#define SOCKET_DATA 0			// 有数据到来
#define SOCKET_CLOSE 1			// 连接关闭
#define SOCKET_SUCCESS 2		// 连接成功建立（主动或者被动，并且已加入到epoll）
#define SOCKET_ACCEPT 3			// 被动连接建立（即accept成功返回已连接套接字）但未加入到epoll
#define SOCKET_ERROR 4			// 发生错误
#define SOCKET_EXIT 5			// 退出事件

struct socket_message {
	int id;
	int ud;	           // for accept,ud是新连接的id，for data,size of data
	char * data;
};



#endif

