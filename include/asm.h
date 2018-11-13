#ifndef ASM_H_
#define ASM_H_

static inline void sti(void) {
  asm volatile("sti");
}

static inline void cli(void) {
  asm volatile("cli");
}

#endif
