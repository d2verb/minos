ENTRY(start)

KERN_BASE = 0xc0000000;

SECTIONS {
  . = 0x100000;

  /* ensure that the multiboot header is at the beginning */
  .multiboot :
  {
    *(.multiboot.header)
    *(.multiboot.text)
  }

  . += KERN_BASE;

  .text : AT(ADDR(.text) - KERN_BASE)
  {
    *(.text)
  }

  .data ALIGN(0x1000) : AT(ADDR(.data) - KERN_BASE)
  {
    *(.data)
    *(.rodata*)
  }

  .bss ALIGN(0x1000) : AT(ADDR(.bss) - KERN_BASE)
  {
    *(.bss)
  }

  /DISCARD/ : {
    *(.eh_frame)
    *(.comment*)
  }
}
