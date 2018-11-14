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

  // pushed by `isrx`
  unsigned int int_no;
  unsigned int err_code;

  // pushed by the processor
  unsigned int eip;
  unsigned int cs;
  unsigned int eflags;
  unsigned int useresp;
  unsigned int ss;
};

extern unsigned int isr_vectors[256];
void isr_handler(struct trapframe tf);

#define IRQ0 32

#endif
