#ifndef ASM_H_
#define ASM_H_

static inline void hlt(void) {
  asm volatile("hlt");
}

static inline void sti(void) {
  asm volatile("sti");
}

static inline void cli(void) {
  asm volatile("cli");
}

static inline ushort inb(ushort port) {
  uchar res;
  asm volatile("inb %1, %0"
             : "=a"(res)
             : "Nd"(port));
  return res;
}

static inline void outb(ushort port, uchar data) {
  asm volatile("outb %0, %1"
             :
             : "a"(data), "Nd"(port)
             :);
}

static inline void set_cr3(uint pa) {
  asm volatile("movl %0, %%cr3" : : "r"(pa));
}

#endif
