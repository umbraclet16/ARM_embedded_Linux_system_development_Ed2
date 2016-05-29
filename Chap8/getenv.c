// filename  getenv.c – 获取环境变量测试
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
  char *env_path = "PATH";		// 打算获取的环境变量名称
  char *env_value = NULL;		// 环境变量值
 
  env_value = getenv(env_path);	// 使用系统函数获取指定环境变量
  if (NULL==env_value)			// 检查是否获取到变量的值
    printf("Not found!\n");
  printf("Get Env PATH:\n%s", env_value);	// 输出PATH环境变量的值
  return 0;
}
