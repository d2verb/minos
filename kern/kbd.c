#include <type.h>
#include <kbd.h>
#include <asm.h>
#include <util.h>
#include <pic.h>

struct key_state key_state;
uchar scan_code;

// see: https://so-zou.jp/pc/keyboard/scan-code.htm
char key_map[2][256] = {
  {
    // alphabet
    [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r',
    [0x14] = 't', [0x15] = 'y', [0x16] = 'u', [0x17] = 'i',
    [0x18] = 'o', [0x19] = 'p', [0x1e] = 'a', [0x1f] = 's',
    [0x20] = 'd', [0x21] = 'f', [0x22] = 'g', [0x23] = 'h',
    [0x24] = 'j', [0x25] = 'k', [0x26] = 'l', [0x2c] = 'z',
    [0x2d] = 'x', [0x2e] = 'c', [0x2f] = 'v', [0x30] = 'b',
    [0x31] = 'n', [0x32] = 'm',

    // number
    [0x2] = '1', [0x3] = '2', [0x4] = '3', [0x5] = '4',
    [0x6] = '5', [0x7] = '6', [0x8] = '7', [0x9] = '8',
    [0xa] = '9', [0xb] = '0',

    // etc
    [0x39] = ' ', [0x1a] = '[', [0x1b] = ']', [0x2b] = '\\',
    [0x27] = ';', [0x28] = '\'', [0x33] = ',', [0x34] = '.',
    [0x35] = '/', [0xc] = '-', [0xd] = '=',
  },
  {
    // [SHIFT] alphabet
    [0x10] = 'Q', [0x11] = 'W', [0x12] = 'E', [0x13] = 'R',
    [0x14] = 'T', [0x15] = 'Y', [0x16] = 'U', [0x17] = 'I',
    [0x18] = 'O', [0x19] = 'P', [0x1e] = 'A', [0x1f] = 'S',
    [0x20] = 'D', [0x21] = 'F', [0x22] = 'G', [0x23] = 'H',
    [0x24] = 'J', [0x25] = 'K', [0x26] = 'L', [0x2c] = 'Z',
    [0x2d] = 'X', [0x2e] = 'C', [0x2f] = 'V', [0x30] = 'B',
    [0x31] = 'N', [0x32] = 'M',

    // [SHIFT] number
    [0x2] = '!', [0x3] = '@', [0x4] = '#', [0x5] = '$',
    [0x6] = '%', [0x7] = '^', [0x8] = '&', [0x9] = '*',
    [0xa] = '(', [0xb] = ')',

    // etc
    [0x39] = ' ', [0x1a] = '{', [0x1b] = '}', [0x2b] = '|',
    [0x27] = ':', [0x28] = '"', [0x33] = '<', [0x34] = '>',
    [0x35] = '?', [0xc] = '_', [0xd] = '+',
  }
};

void kbd_init(void) {
  scan_code = 0;

  key_state.caps = 0;
  key_state.alt = 0;
  key_state.shift = 0;
  key_state.ctrl = 0;
  key_state.numlock = 0;
  key_state.scrolllock = 0;
  key_state.insert = 0;

  pic_clr_mask(PIC1_IMR, PIC_IMR_MASK_IRQ1);

  printk("kbd_init() done!\n");
}

uchar kbd_read_enc_buf(void) {
  return inb(KBD_ENC_BUF);
}