#include <type.h>
#include <multiboot2.h>
#include <mem.h>
#include <util.h>

extern char _kern_end[];

static uchar *nextfree;
static uint npages;


/* Allocate page unit memory.
 * This allocator is only unsed in boottime */
void *boot_alloc(uint n) {
  nextfree = (uchar *)ROUNDUP(nextfree, PAGE_SIZE);

  /* Kernel only has 1GB available memory. */
  if (V2P(nextfree) + PAGE_SIZE * n > KERN_SIZE)
    panic("Out of the memory");

  /* We parepared 1GB virtual memory for kernel,
   * but available physical memory can be less than
   * 1GB. Let's check it. */
  if (V2P(nextfree) + PAGE_SIZE * n > npages * PAGE_SIZE)
    panic("Out of the memory");

  void *result = nextfree;
  nextfree += PAGE_SIZE * n;

  return result;
}

void mem_detect(uint *mbi) {
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
  npages = ROUNDDOWN(mem_start + mem_len, PAGE_SIZE);

  /* mem_start is physical address!! */
  if (V2P(_kern_end) >= mem_start)
    mem_start = V2P(_kern_end);

  nextfree = (uchar *)ROUNDUP(P2V(mem_start), PAGE_SIZE);
}

void mem_init(uint *mbi) {
  mem_detect(mbi);
}
