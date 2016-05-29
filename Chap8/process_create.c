#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t pid;

  pid = fork();					// 创建进程
  if (-1==pid) {					// 创建进程失败
    printf("Error to create new process!\n");
    return 0;
  }
  else if (pid==0) {				// 子进程
    printf("Child process!\n");
  } else {						// 父进程
    printf("Parent process! Child process ID: %d\n", pid);
  }

  return 0;
}
