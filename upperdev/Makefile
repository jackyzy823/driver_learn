#
# Makefile for upperdev
#
#
KVER  := $(shell uname -r)
KSRC := /lib/modules/$(KVER)/build
#MODDESTDIR := /lib/modules/$(KVER)/kernel/drivers/char/upperdrv
PRINT_INC = $(PWD)/../softdev
obj-m := upperdev.o

EXTRA_CFLAGS +=-I $(PRINT_INC)
KBUILD_EXTRA_SYMBOLS+=$(PWD)/../softdev/Module.symvers
export KBUILD_EXTRA_SYMBOLS
all: modules

modules:
	$(MAKE) -C $(KSRC) M=$(shell pwd)  modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
