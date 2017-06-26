#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static dev_t first;		// Global variable for the first device number
static struct class *cl;	// Global variable for the device class
static struct cdev c_dev;	// Global variable for the character device structure
static char c;			// Global variable for store the character

static int
my_open (struct inode *i, struct file *f)
{
  return 0;
}

static int
my_release (struct inode *i, struct file *f)
{
  return 0;
}

static ssize_t
my_read (struct file *f, char __user * buf, size_t len, loff_t * off)
{
  static int count = 0;
  count = (count <= 0) ? sizeof c : count - 1;

  if (copy_to_user ((void *) buf, &c, sizeof c) != 0)
    {
      return -EFAULT;
    }
  else
    {
      return count;
    }
}

static ssize_t
my_write (struct file *f, const char __user * buf, size_t len, loff_t * off)
{
  if (copy_from_user ((void *) &c, buf + len - 1, sizeof c) != 0)
    {
      return -EFAULT;
    }
  else
    {
      return len;
    }
}

static struct file_operations pugs_fops = {
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_release,
  .read = my_read,
  .write = my_write
};

static int __init
mystore_init (void)
{
  if (alloc_chrdev_region (&first, 0, 1, "mymisc") < 0)
    return -1;
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
mystore_exit (void)
{
  cdev_del (&c_dev);
  device_destroy (cl, first);
  class_destroy (cl);
  unregister_chrdev_region (first, 1);
  printk (KERN_INFO "mymisc unregistered");
}

module_init (mystore_init);
module_exit (mystore_exit);
MODULE_LICENSE ("GPL");
MODULE_DESCRIPTION ("misc device driver");
MODULE_AUTHOR ("Jongmin Kim <jmkim@pukyong.ac.kr>");
