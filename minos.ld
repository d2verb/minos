ENTRY(start)

SECTIONS {
  . = 0x100000;

  /* ensure that the multiboot header is at the beginning */
  .multiboot :
  {
    *(.multiboot.header)
  }

  .text :
  {
    *(.text)
  }

  .data ALIGN(0x1000) :
  {
    *(.data)
    *(.rodata*)
  }

  .bss ALIGN(0x1000) :
  {
    *(.bss)
  }

  /DISCARD/ : {
    *(.eh_frame)
    *(.comment*)
  }
}
