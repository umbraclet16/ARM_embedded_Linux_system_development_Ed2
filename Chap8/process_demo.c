// process_demo.c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t pid, pid_wait;
  int fd[2];
  char buff[64], *cmd = "exit";

  if (pipe(fd)) {									// 创建管道
    perror("Create pipe fail!");
    return 0;
  }

  pid = fork();
  if (-1==pid) {
    perror("Create process fail!");
    return 0;
  } else if (0==pid) {								// 子进程
    close(fd[1]);									// 关闭写操作
    printf("wait command from parent!\n");
    while(1) {
      read(fd[0], buff, 64);
      if (0==strcmp(buff, cmd)) {
        printf("recv command ok!\n");
        close(fd[0]);
        exit(0);
      }
    }
  } else {										// 父进程
    printf("Parent process! child process id: %d\n", pid);
    close(fd[0]);									// 关闭读操作
    sleep(2);
    printf("Send command to child process.\n");
    write(fd[1], cmd, strlen(cmd)+1);					// 写入命令
    close(fd[1]);
  }

  return 0;
}
