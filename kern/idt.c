#include <idt.h>
#include <isr.h>
#include <pic.h>
#include <asm.h>
#include <printk.h>

static struct gatedesc idt[IDT_ENTRIES];
static struct idtr idtr;

static void set_idt(int n, unsigned int handler) {
  idt[n].offset_lo = handler & 0xffff;
  idt[n].offset_hi = (handler >> 16) & 0xffff;
  idt[n].zero = 0;
  idt[n].sel = 0x10;
  idt[n].flag = 0x8e;
}

static void set_idtr(void) {
  idtr.base = (unsigned int)&idt;
  idtr.limit = 256 * sizeof(struct gatedesc) - 1;
  asm volatile("lidtl (%0)" : : "r"(&idtr));
}

void idt_init(void) {
  for (int i = 0; i < 256; i++)
    set_idt(i, isr_vectors[i]);
  pic_init();
  set_idtr();
  sti();
}
