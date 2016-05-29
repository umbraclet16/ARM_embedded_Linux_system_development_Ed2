// time_client.c - gcc -o c time_client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define TIME_PORT 9090
#define DATA_SIZE 256

int main()
{
  int sock_fd;
  struct sockaddr_in serv;
  int servlen, n;
  char buff[DATA_SIZE];

  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);		// 创建套接字
  if (sock_fd<=0) {
    perror("create socket error!");
    return 0;
  }
  perror("Create socket");

  /* 设置服务端IP和端口 */
  serv.sin_family=AF_INET;
  serv.sin_port=htons(TIME_PORT);					// 监听端口
  serv.sin_addr.s_addr=INADDR_ANY;				// 本机IP
  servlen =sizeof(serv);

  /* 请求时间 */
  strcpy(buff, "time");
  if (-1==sendto(sock_fd, buff,sizeof(buff), 0, (struct sockaddr*)&serv, servlen)) {		// 发送请求
    perror("send data");
    close(sock_fd);
    return 0;
  }
  printf("send time request\n");

  n = recvfrom(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)&serv, &servlen);		// 接收返回
  if (n<=0) {
    perror("recv data!\n");
    close(sock_fd);
    return 0;
  }
  buff[n]='\0';
  printf("time from server: %s", buff);

  /* 退出连接 */
  strcpy(buff, "quit");
  if (-1==sendto(sock_fd, buff,sizeof(buff), 0, (struct sockaddr*)&serv, servlen)) {
    perror("send data");
    close(sock_fd);
    return 0;
  }
  printf("send quit command\n");

  close(sock_fd);								// 关闭套接字
  return 0;
}
