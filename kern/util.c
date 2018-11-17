#include <type.h>
#include <util.h>
#include <asm.h>
#include <vga.h>

void panic(const char *msg) {
  printk("%s\n", msg);

  cli();
  for (;;) {}
}

static int cur_x;
static int cur_y = VGA_HEIGHT;

static void clear_screen(void) {
  vga_clear_with(' ');
  cur_x = cur_y = 0;
}

static void print_ch(char ch) {
  if (cur_y >= VGA_HEIGHT)
    clear_screen();

  if (ch != '\n') {
    vga_write(cur_x, cur_y, ch);

    cur_x++;
    if (cur_x >= VGA_WIDTH) {
      cur_x = 0;
      cur_y++;
    }
  } else {
    cur_x = 0;
    cur_y++;
  }
}

static void print_str(const char *s) {
  while (*s)
    print_ch(*s++);
}

static void print_int(uint val, int base, int sign) {
  static char digits[] = "0123456789abcdef";
  char buf[12];
  int i;

  if (sign && ((int)val < 0 ? 1 : 0)) {
    val = -(int)val;
    print_ch('-');
  }

  i = 0;
  do {
    buf[i++] = digits[val % base];
    val /= base;
  } while(val != 0);

  while (--i >= 0)
    print_ch(buf[i]);
}

void printk(const char *fmt, ...) {
  uint *ap;
  int state;
  char c;
  
  state = 0;
  ap = (uint *)&fmt + 1;
  
  for (int i = 0; fmt[i]; i++) {
    c = fmt[i];
    if (state == 0) {
      if (c == '%')
        state = '%';
      else
        print_ch(c);
    } else {
      switch (c) {
        default:
          print_ch('%');
          print_ch(c);
          break;
        case 's':
          print_str((char *)*ap);
          ap++;
          break;
        case 'd':
          print_int((int)*ap, 10, 1);
          ap++;
          break;
        case 'u':
          print_int((int)*ap, 10, 0);
          ap++;
          break;
        case 'x':
          print_int((int)*ap, 16, 0);
          ap++;
          break;
      }
      state = 0;
    }
  }
}

void memset(uchar *addr, uchar ch, uint n) {
  for (uint i = 0; i < n; i++)
    addr[i] = ch;
}
