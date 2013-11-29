obj-m:=add_sub.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
PRINT_INC = $(PWD)/../include
EXTRA_CFLAGS+=-I $(PRINT_INC)
all:
	make -I $(PRINT_INC) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Module.symvers modules.order .*.cmd
