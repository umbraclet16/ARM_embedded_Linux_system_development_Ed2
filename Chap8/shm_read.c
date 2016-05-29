// shm_read.c --> gcc -o r shm_read.c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int shmid;								// 定义共享内存id
  char *ptr;

  shmid = shmget(0x90, 1024, SHM_W|SHM_R|IPC_EXCL);   // 根据key获得共享内存id
  if (-1==shmid)
    perror("create share memory");

  ptr = shmat(shmid, 0, 0);						// 通过共享内存id获得共享内存地址
  if ((void*)-1==ptr)
    perror("get share memory");

  printf("string in share memory: %s\n", ptr);		// 打印共享内存中的内容

  shmdt(ptr);
  return 0;
}
