#ifndef VGA_H_
#define VGA_H_

enum VgaColor {
  VGA_BLACK = 0,
  VGA_BLUE,
  VGA_GREEN,
  VGA_CYAN,
  VGA_RED,
  VGA_MAGENTA,
  VGA_BROWN,
  VGA_LIGHT_GRAY,
  VGA_DARK_GRAY,
  VGA_LIGHT_BLUE,
  VGA_LIGHT_GREEN,
  VGA_LIGHT_CYAN,
  VGA_LIGHT_RED,
  VGA_PINK,
  VGA_YELLOW,
  VGA_WHITE,
};

#define VGA_ADDR   0xb8000
#define VGA_HEIGHT 25
#define VGA_WIDTH  80

#define VGA_COLOR(fg, bg) ((bg) << 4 | (fg))

void vga_write_with_prop(int x, int y, char ch, uchar prop);
void vga_write(int x, int y, char ch);
void vga_clear_with(char ch);

#endif
