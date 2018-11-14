#include <asm.h>

unsigned int tick = 0;

void timer_init(unsigned int freq) {
  unsigned int divisor = 1193180 / freq;

  unsigned char lo = (unsigned char)(divisor & 0xff);
  unsigned char hi = (unsigned char)((divisor >> 8) & 0xff);

  outb(0x43, 0x36);
  outb(0x40, lo);
  outb(0x40, hi);
}
