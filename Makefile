include ./Makefile.inc

BOOT_DIR = ./boot
KERN_DIR = ./kern

OBJS = $(BOOT_DIR)/head.o \
			 $(BOOT_DIR)/boot.o \
			 $(KERN_DIR)/kern.o

all: minos.iso

minos.iso: minos.elf
	cp minos.elf iso/boot
	grub-mkrescue -o minos.iso iso/

minos.elf: build $(OBJS)
	$(LD) $(LDFLAGS) -T minos.ld $(OBJS) -o minos.elf

build:
	cd $(BOOT_DIR) && make

qemu: minos.iso
	qemu-system-x86_64 -drive format=raw,file=$<

clean:
	cd $(BOOT_DIR) && make clean
	cd $(KERN_DIR) && make clean
	rm -f minos.iso
	rm -f minos.elf
	rm -f iso/boot/minos.elf

.PHONY: clean
