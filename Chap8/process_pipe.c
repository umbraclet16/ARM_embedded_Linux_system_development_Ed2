#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int fd[2];
  pid_t pid;
  char buf[64] = "I'm parent process!\n";		// 父进程要写入管道的信息
  char line[64];

  if (0!=pipe(fd)) {						// 创建管道并检查结果
    fprintf(stderr, "Fail to create pipe!\n");
    return 0;
  }

  pid = fork();							// 创建进程
  if (pid<0) {
    fprintf(stderr, "Fail to create process!\n");
    return 0;
  } else if (0==pid) {						// 父进程
    close(fd[0]);							// 关闭读管道，使得父进程只能向管道写入数据
    write(fd[1], buf, strlen(buf));				// 写数据到管道
    close(fd[1]);							// 关闭写管道
  } else {								// 子进程
    close(fd[1]);							// 关闭写管道，使得子进程只能从管道读取数据
    read(fd[0], line, 64);					// 从管道读取数据
    printf("DATA From Parent: %s", line);
    close(fd[0]);							// 关闭读管道
  }

  return 0;
}
