#include <pic.h>
#include <asm.h>

void pic_init(void) {
  unsigned char a1, a2;

  /* save masks */
  a1 = inb(PIC1_DATA);
  a2 = inb(PIC2_DATA);

  // ICW1
  /* initialize PIC */
  outb(PIC1_COMMAND, 0x11);
  outb(PIC2_COMMAND, 0x11);

  // ICW2: remap IR number
  /* master PIC: IRQ0-IRQ7 to IR32-IR39
   *  slave PIC: IRQ0-IRQ7 to IR40-IR47 */
  outb(PIC1_DATA, 32);
  outb(PIC2_DATA, 32 + 8);

  // ICW3
  /* tell master PIC that slave PIC is connected at IRQ2 */
  outb(PIC1_DATA, 4);
  /* tell slave PIC that you are connected at IRQ2 of master PIC*/
  outb(PIC1_DATA, 2);

  // ICW4
  /* 8086 mode */
  outb(PIC1_DATA, 1);
  outb(PIC2_DATA, 1);

  /* restore masks */
  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);
}

void pic_eoi(unsigned int irq) {
  if (irq >= 8)
    outb(PIC2_COMMAND, 0x20);
  outb(PIC1_COMMAND, 0x20);
}
