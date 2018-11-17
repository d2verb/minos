#include <type.h>
#include <asm.h>

uint tick = 0;

void timer_init(unsigned int freq) {
  uint divisor = 1193180 / freq;

  uchar lo = (uchar)(divisor & 0xff);
  uchar hi = (uchar)((divisor >> 8) & 0xff);

  outb(0x43, 0x36);
  outb(0x40, lo);
  outb(0x40, hi);
}
