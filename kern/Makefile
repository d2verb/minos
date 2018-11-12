include ../Makefile.inc

CFLAGS += -I../include -I.

OBJS = kern.o vga.o printk.o

all: $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -c

.s.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
