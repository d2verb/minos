#include <type.h>
#include <util.h>
#include <idt.h>
#include <timer.h>
#include <asm.h>
#include <mem.h>

void main(uint *mbi, uint magic) {
  const char *message = "Starting minos!";
  printk("%s\n", message);

  idt_init();
  timer_init(100);
  mem_init(mbi);

  cli();
  for (;;) {}
  return;
}
