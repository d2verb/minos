#include <type.h>
#include <pic.h>
#include <asm.h>
#include <util.h>

void pic_set_mask(ushort port, uchar mask) {
  uchar value = inb(port) | mask;
  outb(port, value);
}

void pic_clr_mask(ushort port, uchar mask) {
  uchar value = inb(port) & ~mask;
  outb(port, value);
}

void pic_init(void) {
  uchar a1, a2;

  /* save masks */
  a1 = inb(PIC1_DATA);
  a2 = inb(PIC2_DATA);

  // ICW1
  /* initialize PIC */
  outb(PIC1_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);
  outb(PIC2_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4);

  // ICW2: remap IR number
  /* master PIC: IRQ0-IRQ7 to IR32-IR39
   *  slave PIC: IRQ0-IRQ7 to IR40-IR47 */
  outb(PIC1_DATA, 32);
  outb(PIC2_DATA, 32 + 8);

  // ICW3
  /* tell master PIC that slave PIC is connected at IRQ2 (0000 0100) */
  outb(PIC1_DATA, (1 << 2));
  /* tell slave PIC that you are connected at IRQ2 of master PIC (0000 0010) */
  outb(PIC2_DATA, 2);

  // ICW4
  /* 8086 mode */
  outb(PIC1_DATA, PIC_ICW4_8086);
  outb(PIC2_DATA, PIC_ICW4_8086);

  /* restore masks */
  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);

  /* mask all irq line (no interrupts are allowed now) */
  pic_set_mask(PIC1_IMR, ~PIC_IMR_MASK_IRQ2);
  pic_set_mask(PIC2_IMR, PIC_IMR_MASK_IRQALL);

  printk("pic_init() done!\n");
}

void pic_eoi(uint irq) {
  if (irq >= 8)
    outb(PIC2_COMMAND, 0x20);
  outb(PIC1_COMMAND, 0x20);
}
