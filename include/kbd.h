#ifndef KBD_H_
#define KBD_H_

#define KBD_ENC  0x60
#define KBD_ENC_BUF KBD_ENC
#define KBD_ENC_CMD KBD_ENC

#define KBD_CTRL 0x64
#define KBD_CTRL_STATUS KBD_CTRL
#define KBD_CTRL_CMD KBD_CTRL

#define KBD_OBF (1 << 0)
#define KBD_IBF (1 << 1)
#define KBD_F0  (1 << 2)
#define KBD_F1  (1 << 3)
#define KBD_ST4 (1 << 4)
#define KBD_ST5 (1 << 5)
#define KBD_ST6 (1 << 6)
#define KBD_ST7 (1 << 7)

struct key_state {
  uchar caps;
  uchar alt;
  uchar shift;
  uchar ctrl;
  uchar numlock;
  uchar scrolllock;
  uchar insert;
};

extern struct key_state key_state;
extern uchar scan_code;
extern char key_map[2][256];

void kbd_init(void);
uchar kbd_read_enc_buf(void);

#endif
