#ifndef IDT_H_
#define IDT_H_

struct gatedesc {
  unsigned short offset_lo;
  unsigned short sel;
  unsigned char  zero;
  unsigned char  flag;
  unsigned short offset_hi;
} __attribute__((packed));

typedef struct gatedesc gatedesc_t;

struct idtr {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

typedef struct idtr idtr_t;

#define IDT_ENTRIES 256

void idt_init(void);

#endif
