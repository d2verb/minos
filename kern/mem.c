#include <type.h>
#include <multiboot2.h>
#include <mem.h>
#include <util.h>
#include <asm.h>

extern char _kern_end[];

static uchar *nextfree;
static uint npages;

struct page {
  uint ref;
  struct page *next;
};

typedef struct page page_t;

static page_t *pages;
static page_t *free_pages;

pde_t *kern_pgdir;

/* Allocate page unit memory.
 * This allocator is only unsed in boottime */
static void *boot_alloc(uint nbytes) {
  nbytes = ROUNDUP(nbytes, PAGE_SIZE);
  nextfree = (uchar *)ROUNDUP(nextfree, PAGE_SIZE);

  /* Kernel only has 1GB available memory. */
  if (KV2P(nextfree) + nbytes > KERN_SIZE)
    panic("Out of the memory");

  /* We parepared 1GB virtual memory for kernel,
   * but available physical memory can be less than
   * 1GB. Let's check it. */
  if (KV2P(nextfree) + nbytes > npages * PAGE_SIZE)
    panic("Out of the memory");

  void *result = nextfree;
  nextfree += nbytes;

  return result;
}

static void mem_detect(uint *mbi) {
  /* Find available ram area starting at 1MB
   * and get the area length */
  multiboot_tag_t *tag;
  multiboot_tag_mmap_t *mmap_tag;
  multiboot_mmap_entry_t *ent;

  uint mem_start;
  uint mem_len;
  for (tag = (multiboot_tag_t *)(mbi + 2);
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

      printk("[mmap] base_addr = 0x%x, length = %dB, type = %d\n", mem_start, mem_len, ent->type);

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
  if (KV2P(_kern_end) >= mem_start)
    mem_start = KV2P(_kern_end);

  nextfree = (uchar *)ROUNDUP(P2KV(mem_start), PAGE_SIZE);
}

static void page_init(void) {
  uint pa, va;
  for (uint i = 0; i < npages; i++) {
    pa = i * PAGE_SIZE;
    va = pa + KERN_BASE;

    if (va < (uint)boot_alloc(0)) {
      /* We assume area under `nextfree` are all used. */
      pages[i].ref = 1;
      pages[i].next = NULL;
    } else {
      pages[i].ref = 0;
      pages[i].next = free_pages;
      free_pages = &pages[i];
    }
  }
}

/* Allocate one page. */
static page_t *page_alloc(void) {
  page_t *result = free_pages;
  if (!result)
    panic("Out of the memory");

  free_pages = free_pages->next;

  result->ref++;
  result->next = NULL;
  return result;
}

/* Try to free the given page.
 * If the ref counter reaches 0, add the page into free list */
static void page_free(page_t *page) {
  if (!page)
    return;

  page->ref--;
  if (page->ref != 0)
    return;

  page->next = free_pages;
  free_pages = page;
}

static inline uint page2pa(page_t *page) {
  return ((uint)page - (uint)pages) / sizeof(page_t) * PAGE_SIZE;
}

static inline uint page2kva(page_t *page) {
  return P2KV(page2pa(page));
}

static pte_t *pgdir_get_pte(pde_t *pgdir, uint va) {
  uint pde = pgdir[PDX(va)];
  pte_t *pt;

  if (pde != 0) {
    pt = P2KV(PTADDR(pde));
    return pt + PTX(va);
  }

  page_t *new_pt = page_alloc();
  memset(page2kva(new_pt), 0, PAGE_SIZE);

  pgdir[PDX(va)] = page2pa(new_pt) | PDE_P | PDE_W;
  return (pte_t *)page2kva(new_pt) + PTX(va);
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

static uint nfree_pages(void) {
  uint n = 0;
  page_t *page = free_pages;
  while (page) {
    n++;
    page = page->next;
  }
  return n;
}

static void dump_pgdir(pde_t *pgdir) {
  pde_t *pde;
  uint i = 0;
  for (pde = pgdir; pde < pgdir + 1024; pde++, i++) {
    printk("[pde] pgdir #%d:", i);
    if (*pde == 0) printk("NOT MAPPED");
    else printk("%x\n", PTADDR(*pde) + KERN_BASE);
  }
}

void mem_init(uint *mbi) {
  uint n;

  mem_detect(mbi);

  kern_pgdir = boot_alloc(PAGE_SIZE);
  memset(kern_pgdir, 0, PAGE_SIZE);

  pages = boot_alloc(npages * sizeof(page_t));
  memset(pages, 0, ROUNDUP(npages * sizeof(page_t), PAGE_SIZE));

  page_init();

  printk("Avaiable pages = %u\n", nfree_pages());

  n = ROUNDDOWN(0xffffffff - KERN_BASE, PAGE_SIZE);
  page_map(kern_pgdir, KERN_BASE, n, 0, PTE_P | PTE_W);

  printk("Avaiable pages = %u\n", nfree_pages());
  printk("Done!\n");
}
