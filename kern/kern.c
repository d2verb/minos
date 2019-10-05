#include <type.h>
#include <util.h>
#include <idt.h>
#include <timer.h>
#include <kbd.h>
#include <asm.h>
#include <mem.h>

void main(uint *multiboot_info, uint magic) {
  const char *message = "Starting minos!";
  printk("%s\n", message);

  idt_init();
  timer_init(100);
  mem_init(multiboot_info);
  kbd_init();
  
  // cli();
  for (;;) {}
  return;
}
