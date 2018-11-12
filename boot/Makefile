include ../Makefile.inc

OBJS = head.o \
			 boot.o

all: $(OBJS)

.s.o:
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f head.o boot.o
