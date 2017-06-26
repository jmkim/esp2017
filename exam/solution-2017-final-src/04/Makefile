ifneq (${KERNELRELEASE},)
	obj-m := mymisc.o
else
	KERNEL_SOURCE := /usr/src/linux-headers-`uname -r`
	PWD := $(shell pwd)
default:
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} modules

clean:
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} clean
endif
