#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static
int
module_begin(void)
{
    printk("Hello, world!\n");
    return 0;
}

static
void
module_end(void)
{
    printk("Bye, world!\n");
}

module_init(module_begin);
module_exit(module_end);
