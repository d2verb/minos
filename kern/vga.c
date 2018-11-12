#include <vga.h>

void vga_write(int x, int y, char ch) {
  vga_write_with_prop(ch, x, y, 7);
}

void vga_write_with_prop(int x, int y, char ch, char prop) {
  *((char *)VGA_ADDR + (x + y * VGA_WIDTH) * 2) = ch;
  *((char *)VGA_ADDR + (x + y * VGA_WIDTH) * 2 + 1) = prop;
}
