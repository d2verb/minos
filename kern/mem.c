#include <multiboot2.h>
#include <mem.h>
#include <printk.h>
#include <panic.h>

extern char _kern_end[];
static unsigned char *alloc_top;
static unsigned char *alloc_end;

/* Allocate page unit memory.
 * This allocator is only unsed in boottime */
void *boottime_alloc(void) {
  alloc_top = (unsigned char *)ROUNDUP(alloc_top, PAGE_SIZE);
  if (alloc_top + PAGE_SIZE > alloc_end)
    panic("Out of the memory.");

  void *ret = alloc_top;
  alloc_top += PAGE_SIZE;
  return ret;
}

void mem_init(unsigned int *mbi) {
  /* Find available ram area starting at 1MB
   * and get the area length */
  multiboot_tag_t *tag;
  multiboot_tag_mmap_t *mmap_tag;
  multiboot_mmap_entry_t *ent;

  unsigned int mem_start;
  unsigned int mem_len;
  for (tag = (multiboot_tag_t *)(mbi + 2);
       tag->type != MULTIBOOT_TAG_END;
       tag = (multiboot_tag_t *)((unsigned char *)tag + ((tag->size + 7) & ~7)))
  {
    if (tag->type != MULTIBOOT_TAG_MMAP)
      continue;

    mmap_tag = (multiboot_tag_mmap_t *)tag;
    for (ent = mmap_tag->entries;
         (unsigned char *)ent < (unsigned char *)mmap_tag + mmap_tag->size;
         ent = (multiboot_mmap_entry_t *)((unsigned int)ent + mmap_tag->entry_size))
    {
      if ((ent->addr >> 32) & 0xffffffff != 0)
        continue;

      if (ent->addr < 1 * 1024 * 1024)
        continue;

      if (ent->type != MULTIBOOT_MEM_AVAILABLE)
        continue;

      mem_start = ent->addr;
      mem_len = ent->len;
      goto found;
    }
  }
not_found:
  panic("Available RAM staring at 1MB is not found.");

found:

  printk("Available RAM found: base_addr = 0x%x, length = %uKB\n", mem_start, mem_len / 1024);

  if ((unsigned int)_kern_end < mem_start)
    alloc_top = (unsigned char *)ROUNDUP(mem_start + KERN_BASE, PAGE_SIZE);
  else
    alloc_top = (unsigned char *)ROUNDUP(_kern_end + KERN_BASE, PAGE_SIZE);

  alloc_end = (unsigned char *)ROUNDDOWN(mem_start + mem_len + KERN_BASE, PAGE_SIZE);
}
