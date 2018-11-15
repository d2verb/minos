#include <printk.h>
#include <panic.h>
#include <asm.h>

void panic(const char *msg) {
  printk("%s\n", msg);

  cli();
  for (;;) {}
}
