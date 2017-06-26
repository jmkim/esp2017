/*
 * Sample kobject implementation
 *
 * Copyright (C) 2004-2007 Greg Kroah-Hartman <greg@kroah.com>
 * Copyright (C) 2007 Novell Inc.
 *
 * Released under the GPL version 2 only.
 *
 */
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

static ssize_t
kitty_show (struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
  return sprintf (buf, "miaow\n");
}

static struct kobj_attribute kitty_attribute =
__ATTR (kitty, 0444, kitty_show, NULL);


static struct attribute *attrs[] = {
  &kitty_attribute.attr,
  NULL,				/* need to NULL terminate the list of attributes */
};

static struct attribute_group attr_group = {.attrs = attrs, };

static struct kobject *example_kobj;

static int __init
example_init (void)
{
  int retval;

  example_kobj = kobject_create_and_add ("mykobject", kernel_kobj);
  if (!example_kobj)
    {
      return -ENOMEM;
    }

  retval = sysfs_create_group (example_kobj, &attr_group);
  if (retval)
    {
      kobject_put (example_kobj);
    }

  return retval;
}

static void __exit
example_exit (void)
{
  kobject_put (example_kobj);
}

module_init (example_init);
module_exit (example_exit);
MODULE_LICENSE ("GPL");
MODULE_AUTHOR
  ("Greg Kroah-Hartman <greg@kroah.com>, Jongmin Kim <jmkim@pukyong.ac.kr>");
