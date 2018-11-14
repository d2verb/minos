include ../Makefile.inc

CFLAGS += -I../include -I.

OBJS = kern.o vga.o printk.o isr.o israsm.o idt.o pic.o timer.o

all: israsm.s $(OBJS)

israsm.s: israsm.py
	python israsm.py > israsm.s

.c.o:
	$(CC) $(CFLAGS) $< -c

.s.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f israsm.s $(OBJS)
