#ifndef ASM_H_
#define ASM_H_

static inline void sti(void) {
  asm volatile("sti");
}

static inline void cli(void) {
  asm volatile("cli");
}

static inline unsigned short inb(unsigned short port) {
  unsigned char res;
  asm volatile("inb %%dx, %%al"
             : "=a"(res)
             : "d"(port)
             : "%eax", "%edx");
  return res;
}

static inline void outb(unsigned short port, unsigned char data) {
  asm volatile("outb %%al, %%dx"
             :
             : "a"(data), "d"(port)
             : "%eax", "%edx");
}

static inline unsigned short inw(unsigned short port) {
  unsigned short res;
  asm volatile("inw %%dx, %%ax"
             : "=a"(res)
             : "d"(port)
             : "%eax", "%edx");
  return res;
}

static inline void outw(unsigned short port, unsigned short data) {
  asm volatile("outw %%ax, %%dx"
             :
             : "a"(data), "d"(port)
             : "%eax", "%edx");
}

#endif
