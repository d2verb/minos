#include <type.h>
#include <idt.h>
#include <isr.h>
#include <pic.h>
#include <asm.h>
#include <util.h>

static gatedesc_t idt[IDT_ENTRIES];
static idtr_t idtr;

static void set_idt(int n, uint handler) {
  idt[n].offset_lo = handler & 0xffff;
  idt[n].offset_hi = (handler >> 16) & 0xffff;
  idt[n].zero = 0;
  idt[n].sel = 0x10;
  idt[n].flag = 0x8e;
}

static void set_idtr(void) {
  idtr.base = (uint)&idt;
  idtr.limit = 256 * sizeof(gatedesc_t) - 1;
  asm volatile("lidtl (%0)" : : "r"(&idtr));
}

void idt_init(void) {
  for (int i = 0; i < 256; i++)
    set_idt(i, isr_vectors[i]);
  pic_init();
  set_idtr();
  sti();

  printk("idt_init() done!\n");
}
