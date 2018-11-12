section .multiboot_header

header_start:
  dd 0xe85250d6                 ; magic number
  dd 0x00000000                 ; protected mode
  dd header_end - header_start  ; header length
  ; checksum
  dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

  dw 0x0000                     ; type
  dw 0x0000                     ; flags
  dd 0x00000008                 ; size
header_end:
