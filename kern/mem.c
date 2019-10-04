#include <type.h>
#include <multiboot2.h>
#include <mem.h>
#include <util.h>
#include <asm.h>

extern char _kern_end[];

static uchar *nextfree;
static uint npages;

pde_t *kern_pgdir;

/* Allocate page unit memory.
 * This allocator is only unsed in boottime */
static void *boot_alloc(uint nbytes) {
  nbytes = ROUNDUP(nbytes, PAGE_SIZE);
  nextfree = (uchar *)ROUNDUP(nextfree, PAGE_SIZE);

  /* Kernel only has 1GB available memory. */
  if (V2P(nextfree) + nbytes > KERN_SIZE)
    panic("Out of the memory");

  /* We parepared 1GB virtual memory for kernel,
   * but available physical memory can be less than
   * 1GB. Let's check it. */
  if (V2P(nextfree) + nbytes > npages * PAGE_SIZE)
    panic("Out of the memory");

  void *result = nextfree;
  nextfree += nbytes;

  return result;
}

static void mem_detect(uint *multiboot_info) {
  /* Find available ram area starting at 1MB
   * and get the area length */
  multiboot_tag_t *tag;
  multiboot_tag_mmap_t *mmap_tag;
  multiboot_mmap_entry_t *ent;

  uint mem_start;
  uint mem_len;
  for (tag = (multiboot_tag_t *)(multiboot_info + 2);
       tag->type != MULTIBOOT_TAG_END;
       tag = (multiboot_tag_t *)((uchar *)tag + ((tag->size + 7) & ~7)))
  {
    if (tag->type != MULTIBOOT_TAG_MMAP)
      continue;

    mmap_tag = (multiboot_tag_mmap_t *)tag;
    for (ent = mmap_tag->entries;
         (uchar *)ent < (uchar *)mmap_tag + mmap_tag->size;
         ent = (multiboot_mmap_entry_t *)((uint)ent + mmap_tag->entry_size))
    {
      mem_start = ent->addr;
      mem_len = ent->len;

      printk("[mmap] base_addr = 0x%x, length = %xB, type = %d\n", mem_start, mem_len, ent->type);

      /* Check base address is less than 4GB.
       * minos doesn't support memory bigger than 4GB. */
      if ((ent->addr >> 32) & 0xffffffff != 0)
        continue;

      /* We only use available memory. */
      if (ent->type != MULTIBOOT_MEM_AVAILABLE)
        continue;

      /* We discard the availabe memories under 1MB. */
      if (ent->addr < 1 * 1024 * 1024)
        continue;

      goto found;
    }
  }
not_found:
  panic("Available RAM staring at 1MB is not found.");

found:
  printk("Available RAM found: base_addr = 0x%x, length = %uKB\n", mem_start, mem_len / 1024);

  /* how many pages we can use. */
  npages = ROUNDDOWN(mem_start + mem_len, PAGE_SIZE) / PAGE_SIZE;

  /* mem_start is physical address!! */
  if (V2P(_kern_end) >= mem_start)
    mem_start = V2P(_kern_end);

  nextfree = (uchar *)ROUNDUP(P2V(mem_start), PAGE_SIZE);
}

static pte_t *pgdir_get_pte(pde_t *pgdir, uint va) {
  uint pde = pgdir[PDX(va)];
  pte_t *pt;

  // if page direct entry exists
  if (pde != 0) {
    pt = (pte_t *)P2V(PTADDR(pde));
    return pt + PTX(va);
  }

  pte_t *new_pt = boot_alloc(1024);
  memset((uchar *)new_pt, 0, PAGE_SIZE);

  pgdir[PDX(va)] = V2P(new_pt) | PDE_P | PDE_W;
  return new_pt + PTX(va);
}

/* map [va, va + n) to [pa, pa + n) */
static void page_map(pde_t *pgdir,
    uint va,
    uint n,
    uint pa,
    uint prop) {

  pte_t *pte;
  uint base_va = va;

  for (; va < base_va + n; va += PAGE_SIZE, pa += PAGE_SIZE) {
    pte = pgdir_get_pte(pgdir, va);
    *pte = prop | pa;
  }
}

void mem_init(uint *multiboot_info) {
  mem_detect(multiboot_info);

  // create new page table
  kern_pgdir = boot_alloc(PAGE_SIZE);
  memset((uchar *)kern_pgdir, 0, PAGE_SIZE);
  
  uint n = ROUNDDOWN((uint)0xffffffff - KERN_BASE, PAGE_SIZE);

  // create new mapping (4KB granularity)
  // TODO: 0xffff0000 doesn't have mapping...
  page_map(kern_pgdir, KERN_BASE, n, 0, PTE_P | PTE_W);
  page_map(kern_pgdir, 0, 1 * MB, 0, PTE_P | PTE_W);

  set_cr3(V2P(kern_pgdir));

  printk("mem_init() done!\n");
}
