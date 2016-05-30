/* 注意POSIX操作文件函数使用不同的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <errno.h>


extern int errno;

int main()
{
	int fd;							// 注意，文件描述符是整型值
	char buf[64] = "this is a posix file!(line1)\n";
	off_t curr_pos;
	int file_mode;
	
	fd = open("./posix.data", O_CREAT|O_RDWR|O_EXCL, S_IRWXU); 
//打开一个不存在的文件，并创建文件，权限是用户可读写执行
	if (-1==fd) {  // 检查文件打开是否成功
		switch (errno) {
			case EEXIST:				// 文件已存在
				printf("File exist!\n");
				break;
			default:					// 其他错误
				printf("open file fail!\n");
				break;
		}
		return 0;
	}
	
	write(fd, buf, strlen(buf));				// 把字符串写入文件
	
	curr_pos = lseek(fd, 0, SEEK_CUR);		// 取得当前文件偏移量位置
	printf("File Point at: %d\n", curr_pos);
	
	lseek(fd, 0, SEEK_SET);				// 把文件偏移量移动到文件开头
	
	strcpy(buf, "File Pointer Moved!\n");
	write(fd, buf, strlen(buf));				// 把新的数据写入文件
	
	file_mode = fcntl(fd, F_GETFL);		// 获取文件状态标记
	if (-1!=file_mode) {
		switch (file_mode&O_ACCMODE) {	// 检查文件状态
			case O_RDONLY:
				printf("file mode is READ ONLY\n");
				break;
			case O_WRONLY:
				printf("file mode is WRITE ONLY\n");
				break;
			case O_RDWR:
				printf("file mode is READ & WRITE\n");
				break;
		}
	}
	
	close(fd);
	
	return 0;
	
}
