#include <util.h>
#include <idt.h>
#include <timer.h>
#include <asm.h>
#include <mem.h>

void main(unsigned int *mbi, unsigned int magic) {
  const char *message = "Starting minos!";
  printk("%s\n", message);

  idt_init();
  timer_init(100);
  mem_init(mbi);

  printk("alloc mem: 0x%x\n", boottime_alloc());
  printk("alloc mem: 0x%x\n", boottime_alloc());
  printk("alloc mem: 0x%x\n", boottime_alloc());

  cli();
  for (;;) {}
  return;
}
