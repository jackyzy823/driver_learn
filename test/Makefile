obj-m:=test.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
SYMBOL_INC=$(obj)/../include
PRINT_INC = $(PWD)/../include
EXTRA_CFLAGS+=-I $(PRINT_INC)
KBUILD_EXTRA_SYMBOLS=$(obj)/../print/Module.symvers
all:
	make -I $(PRINT_INC) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c Module.symvers modules.order .*.cmd
