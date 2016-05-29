#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bye(void)					// 退出时回调的函数
{
  printf("That was all, folks\n");
}

void bye1(void)					// 退出时回调的函数
{
  printf("This should called first!\n");
}

int main()
{
  long a;
  int i;

  i = atexit(bye);					// 设置退出回调函数并检查返回结果
  if (i != 0) {
    fprintf(stderr, "cannot set exit function bye\n");
    return EXIT_FAILURE;
  }

  i = atexit(bye1);				// 设置退出回调函数并检查返回结果
  if (i!=0) {
    fprintf(stderr, "cannot set exit function bye1\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
