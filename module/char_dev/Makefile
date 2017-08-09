# makefile for xxx, tested on Ubuntu 14.04 and CentOS 7 
  PWD := $(shell pwd)
  KVER := $(shell uname -r)
  KDIR := /lib/modules/$(KVER)/build
  mychardev-objs := my_chardev_drv.o
  obj-m := mychardev.o 
all:
	$(MAKE) -Werror -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -Werror -C $(KDIR) M=$(PWD) clean
 