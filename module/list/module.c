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
#include <linux/list.h>
#include <asm/dma-mapping.h>

struct staff_book {
    struct list_head staff_list;
    unsigned int number;
};

struct staff_id{
    struct list_head node;
    char *name;
    unsigned int age;
    unsigned int salary;
    int reserve[2];
};

static struct staff_book staff_book;
//struct staff_id *staff;
    
static int __init dev_init(void)  
{
    struct staff_id *tmp_staff;
    struct list_head *tmp_node;
    struct staff_id *min_staff;
    unsigned int i, j;
    
    INIT_LIST_HEAD(&staff_book.staff_list);
    //staff_book.number = 5;
    //staff = kcalloc(staff_book.number, sizeof(struct staff_id), GFP_KERNEL);
    
    tmp_staff = kzalloc(sizeof(struct staff_id), GFP_KERNEL);
    staff_book.number++;
    list_add(&tmp_staff->node, &staff_book.staff_list);
    tmp_staff->name = "San Wang";
    tmp_staff->age = 35;
    tmp_staff->salary = 20000;
    
    tmp_staff = kzalloc(sizeof(struct staff_id), GFP_KERNEL);
    staff_book.number++;
    list_add(&tmp_staff->node, &staff_book.staff_list);
    tmp_staff->name = "Si Li";
    tmp_staff->age = 40;
    tmp_staff->salary = 25000;
    
    tmp_staff = kzalloc(sizeof(struct staff_id), GFP_KERNEL);
    staff_book.number++;
    list_add(&tmp_staff->node, &staff_book.staff_list);
    tmp_staff->name = "Ting Chen";
    tmp_staff->age = 25;
    tmp_staff->salary = 8000;
    
    tmp_staff = kzalloc(sizeof(struct staff_id), GFP_KERNEL);
    staff_book.number++;
    list_add(&tmp_staff->node, &staff_book.staff_list);
    tmp_staff->name = "Hu Zhao";
    tmp_staff->age = 30;
    tmp_staff->salary = 15000;
    
    tmp_staff = kzalloc(sizeof(struct staff_id), GFP_KERNEL);
    staff_book.number++;
    list_add(&tmp_staff->node, &staff_book.staff_list);
    tmp_staff->name = "Men Chao";
    tmp_staff->age = 28;
    tmp_staff->salary = 12000;
    
    printk(KERN_ALERT"before sort\n\n");
    list_for_each(tmp_node, &staff_book.staff_list){
        tmp_staff = list_entry(tmp_node, struct staff_id, node);    /* container_of */
        printk(KERN_ALERT"name: %s\n", tmp_staff->name);
        printk(KERN_ALERT"age: %d\n", tmp_staff->age);
        printk(KERN_ALERT"salary: %d\n\n", tmp_staff->salary);
    }
    
    for(i = staff_book.number; i > 0; i--) {
        j = 0;
        min_staff = NULL;
        list_for_each_entry(tmp_staff, &staff_book.staff_list, node){
            if ((min_staff == NULL) || (min_staff->age > tmp_staff->age))
                min_staff = tmp_staff;
            if (++j == i) {
                list_move_tail(&min_staff->node, &staff_book.staff_list);
                continue;
            }
        }
    }
    
    printk(KERN_ALERT"after sort\n\n");
    list_for_each(tmp_node, &staff_book.staff_list){     
        tmp_staff = (struct staff_id *)tmp_node;    /* struct list_head must in the first place of struct staff_id */
        printk(KERN_ALERT"name: %s\n", tmp_staff->name);
        printk(KERN_ALERT"age: %d\n", tmp_staff->age);
        printk(KERN_ALERT"salary: %d\n\n", tmp_staff->salary);
    }
    
    return 0;  
}  
  
static void __exit dev_exit(void)  
{
    struct staff_id *del_node, *tmp_node;
    
    list_for_each_entry_safe(del_node, tmp_node, &staff_book.staff_list, node) {
        printk(KERN_ALERT"delete: %s\n", del_node->name);
        printk(KERN_ALERT"void * size: %ld\n", sizeof(void *));
        list_del(&del_node->node);
        kfree(del_node);
    }
    //kfree(staff);
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_AUTHOR("Wenping Fan <fping@cnexlabs.com>");
MODULE_LICENSE("GPL");

