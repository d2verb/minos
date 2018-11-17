#ifndef MULTIBOOT2_H_
#define MULTIBOOT2_H_

struct multiboot_tag {
  uint type;
  uint size;
};

typedef struct multiboot_tag multiboot_tag_t;

struct multiboot_mmap_entry {
  ullong addr;
  ullong len;
#define MULTIBOOT_MEM_AVAILABLE         1
#define MULTIBOOT_MEM_RESERVED          2
#define MULTIBOOT_MEM_ACPI_REClAIMABLE  3
#define MULTIBOOT_MEM_NVS               4
  uint type;
  uint zero;
} __attribute__((packed));

typedef struct multiboot_mmap_entry multiboot_mmap_entry_t;

struct multiboot_tag_mmap {
  uint type;
  uint size;
  uint entry_size;
  uint entry_version;
  struct multiboot_mmap_entry entries[0];
};

typedef struct multiboot_tag_mmap multiboot_tag_mmap_t;

#define MULTIBOOT_TAG_END           0
#define MULTIBOOT_TAG_BASIC_MEMINFO 4
#define MULTIBOOT_TAG_MMAP          6

#endif
