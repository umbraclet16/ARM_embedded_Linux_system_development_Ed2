// time_serv.c - gcc -o s time_serv.c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define TIME_PORT 9090
#define DATA_SIZE 256

int main()
{
  int sock_fd;
  struct sockaddr_in local;
  struct sockaddr_in from;
  int fromlen, n;
  char buff[DATA_SIZE];
  time_t cur_time;

  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);		// 建立套接字
  if (sock_fd<=0) {
    perror("create socket error!");
    return 0;
  }
  perror("Create socket");

  /* 设置要绑定的IP和端口 */
  local.sin_family=AF_INET;
  local.sin_port=htons(TIME_PORT);// 监听端口
  local.sin_addr.s_addr=INADDR_ANY;//本机

  /* 绑定本机到套接字 */
  if (0!=bind(sock_fd,(struct sockaddr*)&local,sizeof(local))) {
    perror("bind socket error!");
    close(sock_fd);
    return 0;
  }
  printf("Bind socket");

  fromlen =sizeof(from);
  printf("waiting request from client...\n");

  while (1)
  {
    n = recvfrom(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)&from, &fromlen);	// 接收数据
    if (n<=0) {
      perror("recv data!\n");
      close(sock_fd);
      return 0;
    }
    buff[n]='\0';									// 设置字符串结束符
    printf("client request: %s\n", buff);					// 打印接收到的字符串

    if (0==strncmp(buff, "quit", 4))					// 判断是否退出
      break;

    if (0==strncmp(buff, "time", 4)) {					// 判断是否请求时间
      cur_time = time(NULL);
      strcpy(buff, asctime(gmtime(&cur_time)));			// 生成当前时间字符串
      sendto(sock_fd, buff,sizeof(buff), 0,(struct sockaddr*)&from,fromlen);	// 发送时间给客户端
    }

  }
  close(sock_fd);								// 关闭套接字
  return 0;
}
