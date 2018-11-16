#include <printk.h>
#include <isr.h>
#include <pic.h>
#include <timer.h>

void isr_main(trapframe_t tf) {
  switch (tf.int_no) {
  default:
    printk("interrupt occured: %d\n", tf.int_no);
    break;
  case IRQ0:
    tick++;
    if (tick % 100 == 0)
      printk("[timer] tick: %d\n", tick);
    break;
  }

  if (tf.int_no >= 32)
    pic_eoi(tf.int_no);
}
