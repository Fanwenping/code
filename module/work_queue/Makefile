# makefile for xxx, tested on Ubuntu 14.04 and CentOS 7 
  PWD := $(shell pwd)
  KVER := $(shell uname -r)
  KDIR := /lib/modules/$(KVER)/build
  demo-objs := module.o
  obj-m := demo.o 
all:
	$(MAKE) -Werror -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -Werror -C $(KDIR) M=$(PWD) clean
 