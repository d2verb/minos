#ifndef PIC_H_
#define PIC_H_

#define PIC1            0x20
#define PIC2            0xa0

#define PIC1_COMMAND    PIC1
#define PIC1_STATUS     PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC1_IMR        (PIC1+1)

#define PIC2_COMMAND    PIC2
#define PIC2_STATUS     PIC2
#define PIC2_DATA       (PIC2+1)
#define PIC2_IMR        (PIC2+1)

// interrupt mask register
#define PIC_IMR_MASK_IRQ0   (1 << 0)
#define PIC_IMR_MASK_IRQ1   (1 << 1)
#define PIC_IMR_MASK_IRQ2   (1 << 2)
#define PIC_IMR_MASK_IRQ3   (1 << 3)
#define PIC_IMR_MASK_IRQ4   (1 << 4)
#define PIC_IMR_MASK_IRQ5   (1 << 5)
#define PIC_IMR_MASK_IRQ6   (1 << 6)
#define PIC_IMR_MASK_IRQ7   (1 << 7)
#define PIC_IMR_MASK_IRQALL 0xff

// initialization commands
#define PIC_ICW1_ICW4       (1 << 0) // ICW4 (not) needed
#define PIC_ICW1_SINGLE     (1 << 1) // Single (cascade) mode
#define PIC_ICW1_INTERVAL4  (1 << 2) // Call address interval 4 (8)
#define PIC_ICW1_LEVEL      (1 << 3) // Level triggered (edge) mode
#define PIC_ICW1_INIT       (1 << 4) // Initialization - required!

#define PIC_ICW4_8086       (1 << 0) // 8086/88 (MSC-80/85) mode
#define PIC_ICW4_AUTO       (1 << 1) // Auto (normal) EOI
#define PIC_ICW4_BUF_SLAVE  (1 << 2) // Buffered mode/slave
#define PIC_ICW4_BUF_MASTER (1 << 3) // Buffered mode/master
#define PIC_ICW4_SFNM       (1 << 4) // Special fully nested (not)

void pic_init(void);
void pic_eoi(uint irq);
void pic_set_mask(ushort port, uchar mask);
void pic_clr_mask(ushort port, uchar mask);

#endif
