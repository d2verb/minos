#include <printk.h>
#include <idt.h>
#include <asm.h>

void main(void) {
  const char *message = "Starting minos!";
  printk("%s\n", message);

  idt_init();
  asm volatile("int $2");
  asm volatile("int $3");
  cli();
  return;
}
