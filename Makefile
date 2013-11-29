obj-m := hello.o
#KERNEL_DIR := /lib/modules/$(shell uname -r)/build
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Module.symvers modules.order .*.cmd

