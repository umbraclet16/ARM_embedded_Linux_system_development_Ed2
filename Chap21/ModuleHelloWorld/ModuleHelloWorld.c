/* 内核模块: ModuleHelloWorld.c */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");				// 设置内核模块版权协议
MODULE_AUTHOR("GongLei");				// 设置内核模块作者

/* init function */
static int __init hello_init(void)				// 模块初始化函数
{
  printk(KERN_ALERT "(init)Hello,World!\n");	// 打印一条信息
  return 0;
}

/* exit function */
static void __exit hello_exit(void)				// 模块退出清除函数
{
  printk(KERN_ALERT "(exit)Hello,World!\n");	// 打印一条信息
}

module_init(hello_init);						// 设置模块初始化函数
module_exit(hello_exit);					// 设置模块退出时清除函数
