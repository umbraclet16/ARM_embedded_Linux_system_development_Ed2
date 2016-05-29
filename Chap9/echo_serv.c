// echo_serv.c – gcc –o s echo_serv.c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define EHCO_PORT 8080
#define MAX_CLIENT_NUM 10

int main()
{
  int sock_fd;
  struct sockaddr_in serv_addr;
  int clientfd;
  struct sockaddr_in clientAdd;
  char buff[101];
  socklen_t len;
  int closing =0;
  int n;

  /* 创建socket */
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_fd==-1) {
    perror("create socket error!");
    return 0;
  } else {
    printf("Success to create socket %d\n", sock_fd);
  }

  /* 设置server地址结构 */
  bzero(&serv_addr, sizeof(serv_addr));				// 初始化结构占用的内存
  serv_addr.sin_family = AF_INET;					// 设置地址传输层类型
  serv_addr.sin_port = htons(EHCO_PORT);			// 设置监听端口
  serv_addr.sin_addr.s_addr = htons(INADDR_ANY);		// 设置服务器地址
  bzero(&(serv_addr.sin_zero), 8);

  /* 把地址和套接字绑定 */
  if(bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))!= 0) {
    printf("bind address fail! %d\n", errno);
    close(sock_fd);
    return 0;
  } else {
    printf("Success to bind address!\n");
  }

  /* 设置套接字监听 */
  if(listen(sock_fd ,MAX_CLIENT_NUM) != 0) {
    perror("listen socket error!\n");
    close(sock_fd);
    return 0;
  } else {
    printf("Success to listen\n");
  }

  /* 创建新连接对应的套接字 */
  len = sizeof(clientAdd);
  clientfd = accept(sock_fd, (struct sockaddr*)&clientAdd, &len);
  if (clientfd<=0) {
    perror("accept() error!\n");
    close(sock_fd);
    return 0;
  }

  /* 接收用户发来的数据 */
  while((n = recv(clientfd,buff, 100,0 )) > 0) {
    buff[n] = '\0'; // 给字符串加入结束符
    printf("number of receive bytes = %d data = %s\n", n, buff);		// 打印字符串长度和内容
    fflush(stdout);
    send(clientfd, buff, n, 0);			// 发送字符串内容给客户端
    if(strncmp(buff, "quit", 4) == 0)		// 判断是否是退出命令
      break;
  }

  close(clientfd);						// 关闭新建的连接
  close(sock_fd);					// 关闭服务端监听的socket

  return 0;
}
