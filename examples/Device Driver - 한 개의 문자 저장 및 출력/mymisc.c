#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static dev_t first;             // Global variable for the first device number
static struct class *cl;        // Global variable for the device class
static struct cdev c_dev;       // Global variable for the character device structure
static char c;                  // Glocal variable for store the character

static ssize_t
my_read (struct file *f, char __user * buf, size_t len, loff_t * off)
{
  if(copy_to_user((void *)buf, &c, 1L) != 0)
  { return -EFAULT; }
  else
  { return sizeof c; }
}

static ssize_t
my_write (struct file *f, const char __user * buf, size_t len, loff_t * off)
{
  if(copy_from_user((void *)&c, buf + len - 1, 1L) != 0)
  { return -EFAULT; }
  else
  { return len; }
}

static struct file_operations pugs_fops = {
  .owner = THIS_MODULE,
  .read = my_read,
  .write = my_write
};

static int __init
mymiscdev_init (void)
{
  printk (KERN_INFO "mymiscdev registered");

  if (alloc_chrdev_region (&first, 0, 1, "MyStoreDriver") < 0)
    { return -1; }

  if ((cl = class_create (THIS_MODULE, "chardrv")) == NULL)
    {
      unregister_chrdev_region (first, 1);
      return -1;
    }
  if (device_create (cl, NULL, first, NULL, "mymiscdev") == NULL)
    {
      class_destroy (cl);
      unregister_chrdev_region (first, 1);
      return -1;
    }

  cdev_init (&c_dev, &pugs_fops);
  if (cdev_add (&c_dev, first, 1) == -1)
    {
      device_destroy (cl, first);
      class_destroy (cl);
      unregister_chrdev_region (first, 1);
      return -1;
    }

  return 0;
}

static void __exit
mymiscdev_exit (void)
{
  cdev_del (&c_dev);
  device_destroy (cl, first);
  class_destroy (cl);
  unregister_chrdev_region (first, 1);
  printk (KERN_INFO "mymiscdev unregistered");
}

module_init (mymiscdev_init);
module_exit (mymiscdev_exit);
MODULE_LICENSE ("GPL");
MODULE_DESCRIPTION ("Store one character as variable");
MODULE_AUTHOR ("Jongmin Kim <jmkim@pukyong.ac.kr>");
