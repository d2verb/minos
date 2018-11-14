#include <printk.h>
#include <idt.h>
#include <timer.h>
#include <asm.h>

void main(void) {
  const char *message = "Starting minos!";
  printk("%s\n", message);

  printk("main @ %x\n", (unsigned int)main);

  idt_init();

  /* 100Hz (10msec) */
  timer_init(100);

  for (;;) {}

  return;
}
