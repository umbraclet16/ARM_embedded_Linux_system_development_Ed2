//
// HttpDemo.c
//
// 功能: 使用Http协议从网站获取一个页面
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

void sig_int(int sig);

/* 解析HTTP头的函数 */
int GetHttpHeader(char *buff, char *header);

/* 打印出错信息 */
#define PRINTERROR(s) \
    fprintf(stderr,"\nError at %s, errno = %d\n", s, errno)

/* 主函数 */
int main()
{
  int bytes_all = 0;
  char *host_name = "www.sohu.com";
  int nRet;
  int sock_fd;// socket句柄
  struct sockaddr_in server_addr;
  struct hostent *host_entry;
  char strBuffer[2048] = {0};//存放返回的数据
  char strHeader[1024] = {0};//存放Http请求报文头

  /* 安装SIGINT信号响应函数 */
  signal(SIGINT, sig_int);

  sock_fd = socket(PF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    PRINTERROR("socket()");
    return -1;
  }

  host_entry = gethostbyname(host_name);//获取域名对应的IP地址
  server_addr.sin_port = htons(80);//设置服务端口号
  server_addr.sin_family = PF_INET;//设置socket类型
  server_addr.sin_addr = (*(struct in_addr*)*(host_entry->h_addr_list));

  /* 连接到服务器 */
  nRet = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
  if (nRet == -1){
    PRINTERROR("connect()");
    close(sock_fd);
    return -1;
  }

  /* 构造Http请求报文头 */
  sprintf(strBuffer, "GET / HTTP/1.1\r\n");
  strcat(strBuffer, "Accept */*\r\n");
  strcat(strBuffer, "Connection: Keep-Alive\r\n");

  /* 发送Http请求 */
  nRet = send(sock_fd, strBuffer, strlen(strBuffer), 0);
  if (nRet == -1) {
    PRINTERROR("send()");
    close(sock_fd);
    return -1;
  }

  /* 获取服务器返回的页面内容 */
  while(1)
  {
    /* 等待服务器返回页面内容 */
    nRet = recv(sock_fd, strBuffer, sizeof(strBuffer), 0);
    if (nRet == -1)
    {
      PRINTERROR("recv()");
      break;
    }

    bytes_all += nRet;//累加服务器返回页面内容的字节数

    if (0==GetHttpHeader(strBuffer, strHeader)) {
      printf("%s", strHeader);
    }

    /* 检查服务器是否关闭连接 */
    if (nRet == 0) {//没有数据返回表示连接已经关闭
      fprintf(stderr,"\n %d bytes received.\n", bytes_all);
      break;
    }

    /* 打印服务器返回的内容 */
    printf("%s", strBuffer);
  }

  /* 关闭连接 */
  close(sock_fd);

  return 0;

}

void sig_int(int sig)	// 中断信号响应函数
{
  printf("Ha ha, we get SIGINT!\n");
}

/* 获取HTTP协议头 */
int GetHttpHeader(char *buff, char *header)
{
  char *p, *q;
  int i=0;

  p = buff;								// 缓冲区头
  q = header;							// 协议头

  if (NULL==p)							// 参数检查
    return -1;
  if (NULL==q)
    return -1;

  while('\0'!=(*p)) {						// 检查是否字符串结束
    q[i] = p[i];
    if ((p[i]==0x0d)&&(p[i+1]==0x0a)&&
      (p[i+2]==0x0d)&&(p[i+3]==0x0a)) {		// 判断是否句子结尾
      q[i+1] = p[i+1];
      q[i+2] = p[i+2];
      q[i+3] = p[i+3];
      q[i+4] = 0;
      return 0;
    }
    i++;
  }
  return -1;
}
