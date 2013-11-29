#
# Makefile for Softdev
#
#
KVER  := $(shell uname -r)
KSRC := /lib/modules/$(KVER)/build
#MODDESTDIR := /lib/modules/$(KVER)/kernel/drivers/char/upperdrv

obj-m := softdev.o



EXTRA_CFLAGS +=

all: modules

modules:
	$(MAKE) -C $(KSRC) M=$(shell pwd)  modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
