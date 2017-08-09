/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

/***************************************************************************
* FILE NAME: module.c
*
* PURPOSE: demo.
*
* NOTES:
*
***************************************************************************/
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/idr.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/kdev_t.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <asm/dma-mapping.h>

#define MYCHAR_MINORS   0

static int my_char_major = 0;
module_param(my_char_major, int, 0);
static struct class *my_char_class;
static char *mychardev_name = "mychardev";

static int mychar_dev_open(struct inode *inode, struct file *f)
{
    printk(KERN_ALERT"open my char device.\n");  
    return 0;
}

static int mychar_dev_release(struct inode *inode, struct file *f)
{
    printk(KERN_ALERT"close my char device.\n");  
    return 0;
}

static long mychar_dev_ioctl(struct file *f, unsigned int cmd,
                            unsigned long arg)
{
    printk(KERN_ALERT"my char device ioctl.\n");  
    return 0;
}

static const struct file_operations mychar_dev_fops = {
	.owner		= THIS_MODULE,
	.open		= mychar_dev_open,
	.release	= mychar_dev_release,
	.unlocked_ioctl	= mychar_dev_ioctl,
	.compat_ioctl	= mychar_dev_ioctl,
};

static int __init mychar_init(void)  
{
    int result;
    int instance = 0;
    struct device *mydev;
    
    /* register abstract char device */
    result = __register_chrdev(my_char_major, 0, MYCHAR_MINORS,
                               mychardev_name, &mychar_dev_fops);
	if (result < 0)
		return result;
	else if (result > 0)
		my_char_major = result;
    
    /**
    * register device class
    * enable create device node in derectory /dev/
    */
	my_char_class = class_create(THIS_MODULE, mychardev_name);
	if (IS_ERR(my_char_class)) {
		result = PTR_ERR(my_char_class);
		goto unregister_chrdev;
	}
    
    /* create device node */
    mydev = device_create(my_char_class, 0,
			MKDEV(my_char_major, instance),
			0, "mychardev%d", instance);
	if (IS_ERR(mydev)) {
		result = PTR_ERR(mydev);
		goto destroy_class;
	}
    return 0; 

destroy_class:
    class_destroy(my_char_class);
unregister_chrdev:
    __unregister_chrdev(my_char_major, 0, MYCHAR_MINORS, mychardev_name);
    return result;
}  
  
static void __exit mychar_exit(void)  
{
    class_destroy(my_char_class);
    __unregister_chrdev(my_char_major, 0, MYCHAR_MINORS, mychardev_name);
}

module_init(mychar_init);
module_exit(mychar_exit);

MODULE_AUTHOR("Wenping Fan <fping@cnexlabs.com>");
MODULE_LICENSE("GPL");