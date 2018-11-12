#include <vga.h>

void main(void) {
  const char *message = "Starting minos!";

  int x = 0;
  while (message[x] != '\x00') {
    vga_write_with_prop(x, 0, message[x], VGA_COLOR(VGA_BLACK, VGA_WHITE));
    x++;
  }

  return;
}
