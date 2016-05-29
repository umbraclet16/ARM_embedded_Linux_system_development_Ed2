#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_func(void *arg)								// 线程函数
{
  int *val = arg;
  printf("Hi, I'm a thread!\n");
  if (NULL!=arg) {									// 如果参数不为空，打印参数内容
    while(1)
      printf("argument set: %d\n", *val);
  }
}

int main()
{
  pthread_t tid;										// 线程ID
  int t_arg = 100;									// 给线程传入的参数值

  if (pthread_create(&tid, NULL, thread_func, &t_arg))		// 创建线程
    perror("Fail to create thread");

  sleep(1);											// 睡眠1秒，等待线程执行
  printf("Main thread!\n");
  pthread_cancel(tid);									// 取消线程

  return 0;
}
