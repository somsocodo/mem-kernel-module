KBUILD_CFLAGS += -w
# Specify the path for the modules relative to the src/ directory
mem-module-objs := src/main.o src/mem.o src/ioctl.o
obj-m += mem-module.o

# Default target to compile the kernel modules
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

unload:
	sudo rmmod mem-module

# Targets to load the kernel modules. Adjust the path for the ko files.
load:
	sudo insmod mem-module.ko

# Target to clean up build artifacts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Target to clear the kernel log buffer
clear:
	sudo dmesg -c

# Target to view the kernel log buffer
view:
	dmesg -wH