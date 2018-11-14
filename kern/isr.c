#include <printk.h>
#include <isr.h>
#include <pic.h>

void isr_main(struct trapframe tf) {
  printk("interrupt occured: %d\n", tf.int_no);

  if (tf.int_no >= 32)
    pic_eoi(tf.int_no);
}
