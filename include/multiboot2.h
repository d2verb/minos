#ifndef MULTIBOOT2_H_
#define MULTIBOOT2_H_

struct multiboot_tag {
  unsigned int type;
  unsigned int size;
};

typedef struct multiboot_tag multiboot_tag_t;

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

typedef struct multiboot_mmap_entry multiboot_mmap_entry_t;

struct multiboot_tag_mmap {
  unsigned int type;
  unsigned int size;
  unsigned int entry_size;
  unsigned int entry_version;
  struct multiboot_mmap_entry entries[0];
};

typedef struct multiboot_tag_mmap multiboot_tag_mmap_t;

#define MULTIBOOT_TAG_END           0
#define MULTIBOOT_TAG_BASIC_MEMINFO 4
#define MULTIBOOT_TAG_MMAP          6

#endif
