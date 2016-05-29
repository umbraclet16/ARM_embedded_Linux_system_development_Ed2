#include <stdio.h>
 
int main()
{
	FILE *fp = NULL;						// 定义文件指针
	char *buf[3] = {						// 定义三个字符串，供写入文件使用
	        "This is first line!\n",
	        "Second Line!\n",
	        "OK, the last line!\n"};
	char tmp_buf[3][64], *p;				// 定义字符串缓存，供读取文件使用
	int i;
	
	fp = fopen("chap7_demo.dat", "rb+");		// 使用读写方式打开文件，并且把文件长度置0
	if (NULL==fp) {
    printf("error to open file!\n");
    return -1;
	}
	
	// 把三个字符串写入文件
	for (i=0;i<3;i++)
	        fputs(buf[i], fp);
	
	fseek(fp, 0, SEEK_SET);				// 把文件指针设置到文件开头，相当于rewind(fp)
	
	// 从文件读取三个字符串到缓存
	for (i=0;i<3;i++) {
    p = tmp_buf[i];
    fgets(p, 64, fp);
    printf("%s", p);				// 打印刚读取出来的字符串到屏幕
	}
	
	fclose(fp);							// 别忘记关闭文件
	
	return 0;
}
