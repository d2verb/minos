#include <type.h>
#include <util.h>
#include <isr.h>
#include <pic.h>
#include <timer.h>
#include <kbd.h>

void isr_main(trapframe_t tf) {
  uchar ch;

  switch (tf.int_no) {
  default:
    printk("interrupt occured: %d\n", tf.int_no);
    break;
  case IRQ0:
    tick++;
    break;
  case IRQ1:
    ch = kbd_read_enc_buf();

    switch (ch) {
    case 0x2a:
    case 0x36:
      key_state.shift = 1;
      break;
    case 0xaa:
    case 0xb6:
      key_state.shift = 0;
      break;
    }

    if (key_map[key_state.shift][ch] != 0) {
      printk("%c", key_map[key_state.shift][ch]);
    }

    break;
  }

  if (tf.int_no >= 32)
    pic_eoi(tf.int_no);
}
