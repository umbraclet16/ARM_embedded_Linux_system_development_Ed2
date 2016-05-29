// echo_client – gcc –o c echo_client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define EHCO_PORT 8080
#define MAX_COMMAND 5

int main()
{
  int sock_fd;
  struct sockaddr_in serv_addr;

  char *buff[MAX_COMMAND] = {"abc", "def", "test", "hello", "quit"};
  char tmp_buf[100];
  socklen_t len;
  int n, i;

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

  /* 连接到服务端 */
  if (-1==connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
    perror("connect() error!\n");
    close(sock_fd);
    return 0;
  }
  printf("Success connect to server!\n");

  /* 发送并接收缓冲的数据 */
  for (i=0;i<MAX_COMMAND;i++) {
    send(sock_fd, buff[i], 100, 0);						// 发送数据给服务端
    n = recv(sock_fd, tmp_buf, 100, 0);					// 从服务端接收数据
    tmp_buf[n] = '\0';  // 给字符串添加结束标志
    printf("data send: %s receive: %s\n", buff[i], tmp_buf);		// 打印字符串
    if (0==strncmp(tmp_buf, "quit", 4))					// 判断是否是退出命令
      break;
  }

  close(sock_fd);									// 关闭套接字

  return 0;
}