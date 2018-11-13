#include <printk.h>
#include <isr.h>

void isr_handler(struct trapframe tf) {
  printk("interrupt occured: %d\n", tf.int_no);
}
