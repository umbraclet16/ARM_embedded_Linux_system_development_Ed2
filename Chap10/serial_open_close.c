#include     <stdio.h>		/*标准输入输出定义*/             
#include     <stdlib.h>		/*标准函数库定义*/               
#include     <unistd.h>		/*Unix 标准函数定义*/            
#include     <sys/types.h>                                 
#include     <sys/stat.h>                                  
#include     <fcntl.h>		/*文件控制定义*/                 
#include     <termios.h>		/*PPSIX 终端控制定义*/         
#include     <errno.h>		/*错误号定义*/                   
                                                           
int main()                                                 
{                                                          
	int fd;                                                  
                                                           
	fd = open( "/dev/ttyS0", O_RDWR);	// 使用读写方式打开串口
	if (-1 == fd){                                           
		perror("open ttyS0");                                  
		return 0;                                              
	}                                                        
	printf("Open ttyS0 OK!\n");                              
	                                                         
	close(fd);		// 关闭串口                                
	return 0;                                                
}                                                          