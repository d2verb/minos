#ifndef IDT_H_
#define IDT_H_

struct gatedesc {
  ushort offset_lo;
  ushort sel;
  uchar  zero;
  uchar  flag;
  ushort offset_hi;
} __attribute__((packed));

typedef struct gatedesc gatedesc_t;

struct idtr {
  ushort limit;
  uint base;
} __attribute__((packed));

typedef struct idtr idtr_t;

#define IDT_ENTRIES 256

void idt_init(void);

#endif
