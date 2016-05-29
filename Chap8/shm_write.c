// shm_write.c --> gcc -o w shm_write.c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int shmid;							 // 定义共享内存id
  char *ptr;
  char *shm_str = "string in a share memory";

  shmid = shmget(0x90, 1024, SHM_W|SHM_R|IPC_CREAT|IPC_EXCL); // 创建共享内存
  if (-1==shmid)
    perror("create share memory");

  ptr = (char*)shmat(shmid, 0, 0);			// 通过共享内存id获得共享内存地址
  if ((void*)-1==ptr)
    perror("get share memory");

  strcpy(ptr, shm_str);					// 把字符串写入共享内存
  shmdt(ptr);

  return 0;
}
