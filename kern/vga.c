#include <type.h>
#include <vga.h>

void vga_write_with_prop(int x, int y, char ch, uchar prop) {
  *((char *)VGA_ADDR + (x + y * VGA_WIDTH) * 2) = ch;
  *((char *)VGA_ADDR + (x + y * VGA_WIDTH) * 2 + 1) = prop;
}

void vga_write(int x, int y, char ch) {
  vga_write_with_prop(x, y, ch, 7);
}

void vga_clear_with(char ch) {
  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++)
      vga_write(x, y, ch);
  }
}
