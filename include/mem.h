#ifndef MEM_H_
#define MEM_H_

#define ROUNDUP(a, b)   (((unsigned int)(a) + (unsigned int)(b) - 1) / (unsigned int)(b) * (unsigned int)(b))
#define ROUNDDOWN(a, b) ((unsigned int)(a) / (unsigned int)(b) * (unsigned int)(b))

#define PAGE_SIZE 4096
#define KERN_BASE 0xc0000000

void *boottime_alloc(void);
void mem_init(unsigned int *mbi);

#endif
