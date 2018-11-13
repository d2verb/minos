#include <printk.h>
#include <idt.h>
#include <asm.h>

void main(void) {
  const char *message = "Starting minos!";
  printk("%s\n", message);

  printk("main @ %x\n", (unsigned int)main);

  idt_init();
  asm volatile("int $2");
  asm volatile("int $3");
  cli();

  return;
}
