#ifndef PIC_H_
#define PIC_H_

#define PIC1            0x20
#define PIC2            0xa0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

void pic_init(void);
void pic_eoi(uint irq);

#endif
