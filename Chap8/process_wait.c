#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t pid, pid_wait;
  int status;

  pid = fork();							// 创建子进程
  if (-1==pid) {							// 检查是否创建成功
    printf("Error to create new process!\n");
    return 0;
  }
  else if (pid==0) {						// 子进程
    printf("Child process!\n");
  } else {								// 父进程
    printf("Parent process! Child process ID: %d\n", pid);
    pid_wait = waitpid(pid, &status, 0);		// 等待指定进程号的子进程
    printf("Child process %d returned!\n", pid_wait);
  }

  return 0;
}
