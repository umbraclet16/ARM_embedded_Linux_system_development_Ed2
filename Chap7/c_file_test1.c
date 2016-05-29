// 从文件读写成块数据
#include <stdio.h>
int main()
{
	int buf[1024] = {0};
	int *p;
    int i;
	FILE *fp = fopen("./blk_file.dat", "rb+");
	if (NULL == fp)
		return -1;
	fwrite(buf, sizeof(int), 1024, fp);			// 把1024个数据块写入文件流fp，每个数据块4个字节
	
	/* 修改buf的数据，供读取后比较 */
	for (i=0;i<16;i++)
		buf[i] = -1;

	p = &buf[0]; // 设置指针p指向buf，供从文件读取数据使用
	fread(p, sizeof(int), 1024, fp);			// 从文件读取1024个数据块到buf，每个数据块4个字节
	
	/* 打印从文件读取的二进制数据 */
	for (i=0;i<1024;i++)
		printf("buf[%d] = %d\n", i, buf[i]);
	
	fclose(fp);							// 最后别忘了关闭文件
	
	return 0;
}
