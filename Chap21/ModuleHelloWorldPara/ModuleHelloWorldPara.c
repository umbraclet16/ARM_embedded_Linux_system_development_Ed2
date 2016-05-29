/* 内核模块: ModuleHelloWorldPara.c */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakespeare");

static int initValue = 0;											// 模块参数 initValue = <int value>
static char *initName = NULL;									// 模块参数 initName = <char*>
module_param(initValue, int, S_IRUGO);
module_param(initName, charp, S_IRUGO);

/* init function */
static int hello_init(void)
{
  printk(KERN_ALERT "initValue = %d initName = %s\n", initValue, initName);	// 打印参数值
  printk(KERN_ALERT "(init)Hello,World!\n");
  return 0;
}

/* exit function */
static void hello_exit(void)
{
  printk(KERN_ALERT "(exit)Hello,World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
