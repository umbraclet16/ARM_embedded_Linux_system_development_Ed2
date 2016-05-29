//test.c
int g_var_a =0;					// 存放在全局已初始化数据区
char g_var_b;					// 存放在BSS区（未初始化全局变量）

int main()
{
	int var_a;					// 存放在栈区
	char var_str[] = “string1”;		// 存放在栈区
	char *p_str1, *p_str2;		// 存放在栈区
	char *p_str3 = “string2”;		// 存放在已初始化数据区 ptr_str3存放在栈区
	static int var_b = 100;		// 全局静态数据，存放在已初始化区

	p_str1 = (char*)malloc(1024);	// 从堆区分配1024字节内存
	p_str2 = (char*)malloc(2048);	// 从堆区分配2048字节内存
	free(p_str1);
	free(p_str2);

	return 0;
}
