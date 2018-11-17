#ifndef ISR_H_
#define ISR_H_

struct trapframe {
  uint ds;

  // pushed by `pusha`
  uint edi;
  uint esi;
  uint ebp;
  uint esp;
  uint ebx;
  uint edx;
  uint ecx;
  uint eax;

  // pushed by `isrx`
  uint int_no;
  uint err_code;

  // pushed by the processor
  uint eip;
  uint cs;
  uint eflags;
  uint useresp;
  uint ss;
};

typedef struct trapframe trapframe_t;

extern uint isr_vectors[256];
void isr_handler(struct trapframe tf);

#define IRQ0 32

#endif
