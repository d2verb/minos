include ../Makefile.inc

OBJS = kern.o

all: $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -c

.s.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f kern.o
