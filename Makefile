include ./Makefile.inc

BOOT_DIR = ./boot
KERN_DIR = ./kern

OBJS = $(BOOT_DIR)/head.o \
			 $(BOOT_DIR)/boot.o \
			 $(KERN_DIR)/kern.o \
			 $(KERN_DIR)/vga.o \
			 $(KERN_DIR)/idt.o \
			 $(KERN_DIR)/isr.o \
			 $(KERN_DIR)/israsm.o \
			 $(KERN_DIR)/pic.o \
			 $(KERN_DIR)/timer.o \
			 $(KERN_DIR)/mem.o \
			 $(KERN_DIR)/util.o \

all: minos.iso

minos.iso: minos.elf
	cp minos.elf iso/boot
	grub-mkrescue -o minos.iso iso/

minos.elf: build $(OBJS)
	$(LD) $(LDFLAGS) -T minos.ld $(OBJS) -o minos.elf

build:
	cd $(BOOT_DIR) && make
	cd $(KERN_DIR) && make

qemu: minos.iso
	qemu-system-x86_64 -drive format=raw,file=$<

qemu-gdb: minos.iso
	qemu-system-x86_64 -drive format=raw,file=$< -nographic -serial mon:stdio -s -S

clean:
	cd $(BOOT_DIR) && make clean
	cd $(KERN_DIR) && make clean
	rm -f minos.iso
	rm -f minos.elf
	rm -f iso/boot/minos.elf

.PHONY: clean
