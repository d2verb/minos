#ifndef MULTIBOOT2_H_
#define MULTIBOOT2_H_

struct multiboot_tag {
  unsigned int type;
  unsigned int size;
};

struct multiboot_tag_basic_meminfo {
  unsigned int type;
  unsigned int size;
  unsigned int mem_lower;
  unsigned int mem_upper;
};

struct multiboot_mmap_entry {
  unsigned long long addr;
  unsigned long long len;
#define MULTIBOOT_MEM_AVAILABLE         1
#define MULTIBOOT_MEM_RESERVED          2
#define MULTIBOOT_MEM_ACPI_REClAIMABLE  3
#define MULTIBOOT_MEM_NVS               4
  unsigned int type;
  unsigned int zero;
} __attribute__((packed));

struct multiboot_tag_mmap {
  unsigned int type;
  unsigned int size;
  unsigned int entry_size;
  unsigned int entry_version;
  struct multiboot_mmap_entry entries[0];
};

#define MULTIBOOT_TAG_END           0
#define MULTIBOOT_TAG_BASIC_MEMINFO 4
#define MULTIBOOT_TAG_MMAP          6

#endif