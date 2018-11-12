#include <printk.h>

void main(void) {
  const char *message = "Starting minos!";
  printk(message);
  return;
}
