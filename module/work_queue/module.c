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
#include <linux/workqueue.h>
#include <asm/dma-mapping.h>

static struct workqueue_struct *mywq = NULL;  
static struct work_struct mywork;  
  
static void work_handler(struct work_struct *data)  
{  
    printk(KERN_ALERT"work handler function.\n");  
}  
  
static int __init dev_init(void)  
{  
    mywq = create_singlethread_workqueue("my_wq");/*创建一个单线程的工作队列*/  
    if (!mywq)  
        return -1;  

    INIT_WORK(&mywork, work_handler);
    queue_work(mywq, &mywork);
    //schedule_work(&mywork); /* put work task in global workqueue */

    return 0;  
}  
  
static void __exit dev_exit(void)  
{  
    destroy_workqueue(mywq);  
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_AUTHOR("Wenping Fan <fping@cnexlabs.com>");
MODULE_LICENSE("GPL");

