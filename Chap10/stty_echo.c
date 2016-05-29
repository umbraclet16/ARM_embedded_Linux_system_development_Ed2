/* stty_echo.c  -  gcc -o stty_echo stty_echo.c */
#include     <stdio.h>		/*标准输入输出定义*/
#include     <stdlib.h>		/*标准函数库定义*/
#include     <unistd.h>		/*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>			/*文件控制定义*/
#include     <termios.h>		/*PPSIX 终端控制定义*/
#include     <errno.h>		/*错误号定义*/


#define STTY_DEV "/dev/ttyS0"
#define BUFF_SIZE 512

int main()
{
  int stty_fd, n;
  char buffer[BUFF_SIZE];
  struct termios opt;

  /* 打开串口设备 */
  stty_fd = open(STTY_DEV, O_RDWR);
  if (-1==stty_fd) {
    perror("open device");
    return 0;
  }
  printf("Open device success, waiting user input ...\n");

  /* 取得当前串口配置 */
  tcgetattr(stty_fd, &opt);
  tcflush(stty_fd, TCIOFLUSH);

  /* 设置波特率 - 19200bps */
  cfsetispeed(&opt, B19200);
  cfsetospeed(&opt, B19200);

  /* 设置数据位 - 8位数据位 */
  opt.c_cflag &= ~CSIZE;
  opt.c_cflag |= CS8;

  /* 设置奇偶位 - 无奇偶校验 */
  opt.c_cflag &= ~PARENB;
  opt.c_iflag &= ~INPCK;


  /* 设置停止位 - 1位停止位 */
  opt.c_cflag &= ~CSTOPB;

  /* 设置超时时间 - 15秒 */
  opt.c_cc[VTIME] = 150;
  opt.c_cc[VMIN] = 0;

  /* 设置写入设备 */
  if (0!=tcsetattr(stty_fd, TCSANOW, &opt)) {
    perror("set baudrate");
    return 0;
  }
  tcflush(stty_fd, TCIOFLUSH);

  /* 读取数据，直到接收到'quit'字符串退出 */
  while(1) {
    n = read(stty_fd, buffer, BUFF_SIZE);
    if (n<=0) {
      perror("read data");
      break;
    }
    buffer[n] = '\0';

    printf("%s", buffer);
    if (0==strncmp(buffer, "quit", 4)) {
      printf("user send quit!\n");
      break;
    }
  }
  printf("Program will exit!\n");

  close(stty_fd);
}
