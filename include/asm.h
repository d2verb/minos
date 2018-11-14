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
  asm volatile("inb %1, %0"
             : "=a"(res)
             : "Nd"(port));
  return res;
}

static inline void outb(unsigned short port, unsigned char data) {
  asm volatile("outb %0, %1"
             :
             : "a"(data), "Nd"(port)
             :);
}

#endif
