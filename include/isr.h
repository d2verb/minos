#ifndef ISR_H_
#define ISR_H_

struct trapframe {
  unsigned int ds;

  // pushed by `pusha`
  unsigned int edi;
  unsigned int esi;
  unsigned int ebp;
  unsigned int esp;
  unsigned int ebx;
  unsigned int edx;
  unsigned int ecx;
  unsigned int eax;

  // pushed by `isrx_entry`
  unsigned int int_no;
  unsigned int err_code;

  // pushed by the processor
  unsigned int eip;
  unsigned int cs;
  unsigned int eflags;
  unsigned int useresp;
  unsigned int ss;
};

extern void isr0_entry(void);
extern void isr1_entry(void);
extern void isr2_entry(void);
extern void isr3_entry(void);
extern void isr4_entry(void);
extern void isr5_entry(void);
extern void isr6_entry(void);
extern void isr7_entry(void);
extern void isr8_entry(void);
extern void isr9_entry(void);
extern void isr10_entry(void);
extern void isr11_entry(void);
extern void isr12_entry(void);
extern void isr13_entry(void);
extern void isr14_entry(void);
extern void isr15_entry(void);
extern void isr16_entry(void);
extern void isr17_entry(void);
extern void isr18_entry(void);
extern void isr19_entry(void);
extern void isr20_entry(void);
extern void isr21_entry(void);
extern void isr22_entry(void);
extern void isr23_entry(void);
extern void isr24_entry(void);
extern void isr25_entry(void);
extern void isr26_entry(void);
extern void isr27_entry(void);
extern void isr28_entry(void);
extern void isr29_entry(void);
extern void isr30_entry(void);
extern void isr31_entry(void);

void isr_common(struct trapframe tf);

#endif
