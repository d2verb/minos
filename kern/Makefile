include ../Makefile.inc

CFLAGS += -I../include -I.

OBJS = kern.o vga.o isr.o israsm.o idt.o pic.o timer.o mem.o util.o

all: israsm.s $(OBJS)

israsm.s: israsm.py
	python israsm.py > israsm.s

.c.o:
	$(CC) $(CFLAGS) $< -c

.s.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f israsm.s $(OBJS)
