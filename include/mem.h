#ifndef MEM_H_
#define MEM_H_

#define ROUNDUP(a, b)   (((uint)(a) + (uint)(b) - 1) / (uint)(b) * (uint)(b))
#define ROUNDDOWN(a, b) ((uint)(a) / (uint)(b) * (uint)(b))

#define PAGE_SIZE 4096        /* 4KB */
#define KERN_BASE 0xc0000000  /* 3GB */
#define KERN_SIZE 0x40000000  /* 1GB */

#define P2V(p)    ((p) + KERN_BASE)
#define V2P(v)    ((v) - KERN_BASE)

#define PTSHIFT   12
#define PDSHIFT   22

#define PTE_P     (1 << 0)
#define PTE_W     (1 << 1)
#define PTE_U     (1 << 2)
#define PTE_PWT   (1 << 3)
#define PTE_PCD   (1 << 4)
#define PTE_A     (1 << 5)
#define PTE_D     (1 << 6)
#define PTE_PAT   (1 << 7)
#define PTE_G     (1 << 8)

#define PDE_P     (1 << 0)
#define PDE_W     (1 << 1)
#define PDE_U     (1 << 2)
#define PDE_PWT   (1 << 3)
#define PDE_PCD   (1 << 4)
#define PDE_A     (1 << 5)
#define PDE_PS    (1 << 7)
#define PDE_G     (1 << 8)

void *boot_alloc(uint n);
void mem_init(uint *mbi);

#endif
