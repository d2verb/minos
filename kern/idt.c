#include <idt.h>
#include <isr.h>
#include <asm.h>

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
  set_idt(0, (unsigned int)isr0);
  set_idt(1, (unsigned int)isr1);
  set_idt(2, (unsigned int)isr2);
  set_idt(3, (unsigned int)isr3);
  set_idt(4, (unsigned int)isr4);
  set_idt(5, (unsigned int)isr5);
  set_idt(6, (unsigned int)isr6);
  set_idt(7, (unsigned int)isr7);
  set_idt(8, (unsigned int)isr8);
  set_idt(9, (unsigned int)isr9);
  set_idt(10, (unsigned int)isr10);
  set_idt(11, (unsigned int)isr11);
  set_idt(12, (unsigned int)isr12);
  set_idt(13, (unsigned int)isr13);
  set_idt(14, (unsigned int)isr14);
  set_idt(15, (unsigned int)isr15);
  set_idt(16, (unsigned int)isr16);
  set_idt(17, (unsigned int)isr17);
  set_idt(18, (unsigned int)isr18);
  set_idt(19, (unsigned int)isr19);
  set_idt(20, (unsigned int)isr20);
  set_idt(21, (unsigned int)isr21);
  set_idt(22, (unsigned int)isr22);
  set_idt(23, (unsigned int)isr23);
  set_idt(24, (unsigned int)isr24);
  set_idt(25, (unsigned int)isr25);
  set_idt(26, (unsigned int)isr26);
  set_idt(27, (unsigned int)isr27);
  set_idt(28, (unsigned int)isr28);
  set_idt(29, (unsigned int)isr29);
  set_idt(30, (unsigned int)isr30);
  set_idt(31, (unsigned int)isr31);

  set_idtr();
  sti();
}
