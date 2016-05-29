// c_memory_test.c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *p_str1, *p_str2;								// 定义两个char*指针

    /* 使用malloc()函数分配内存 */
     p_str1 = (char*)malloc(32);
     if (NULL==p_str1) {								// 检查内存分配是否成功
         printf("Alloc p_str1 memory ERROR!\n");
         return -1;
     }   
 
     /* 使用calloc()函数分配内存 */
     p_str2 = (char*)calloc(32, sizeof(char));
     if (NULL==p_str2) {								// 检查内存是否分配成功
         printf("Alloc p_str2 memory ERROR!\n");
         free(p_str1);									// 注意，这里需要释放p_str1占用的内存
         return -1;
     }   
 
     strcpy(p_str1, "This is a simple sentence.");				// p_str1写入一个字符串
     strcpy(p_str2, p_str1);								// p_str2写入与p_str1相同的字符串
 
     /* 打印p_str1的结果 */
     printf("p_str1 by malloc():\n");
     printf("p_str1 address: 0x%.8x\n", p_str1);				// p_str1的内存地址
     printf("p_str1: %s(%d chars)\n", p_str1, strlen(p_str1));		// p_str1的内容
 
     /* 打印p_str2的结果 */
     printf("p_str2 by calloc():\n");
     printf("p_str2 address: 0x%.8x\n", p_str2);				// p_str2的内存地址
     printf("p_str2: %s(%d chars)\n", p_str2, strlen(p_str2));		// p_str2的内容
 
     /* 为p_str1重新分配内存（减小） */
     p_str1 = (char*)realloc(p_str1, 16);
     if (NULL==p_str1) {								// 检查内存分配结果
         printf("Realloc p_str1 memory ERROR!\n");
         free(p_str2);									// 注意，需要释放p_str2占用的内存
         return -1;
     }   
     p_str1[15] = '\0';									// 写字符串结束符
 
     /* 为p_str2重新分配内存（增大） */
     p_str2 = (char*)realloc(p_str2, 128);
     if (NULL==p_str2) {								// 检查内存分配结果
         printf("Realloc p_str2 memory ERROR!\n");
         free(p_str1);									// 注意，需要释放p_str1占用的内存
         return -1;
     }   
     strcat(p_str2, "The second sentence in extra memory after realloced!");
 
     /* 打印p_str1的结果 */
     printf("p_str1 after realloced\n");
     printf("p_str1 address: 0x%.8x\n", p_str1);				// p_str1的内存地址
     printf("p_str1: %s(%d chars)\n", p_str1, strlen(p_str1));		// p_str1的内容
 
     /* 打印p_str2的结果 */
     printf("p_str2 after realloced:\n");
     printf("p_str2 address: 0x%.8x\n", p_str2);				// p_str2的内存地址
     printf("p_str2: %s(%d chars)\n", p_str2, strlen(p_str2));		// p_str2的内容
 
     /* 注意，最后要释放占用的内存 */
     free(p_str1);										// 释放p_str1占用的内存
     free(p_str2);										// 释放p_str2占用的内存
 
     return 0;
 }
