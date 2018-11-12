ENTRY(start)

SECTIONS {
  . = 1M;

  .boot :
  {
    /* ensure that the multiboot header is at the beginning */
    *(.multiboot_header)
  }

  .text :
  {
    *(.text)
  }

  .bss ALIGN(0x1000) :
  {
    *(.bss)
  }
}
