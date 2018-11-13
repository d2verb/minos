[bits 32]
global start

extern main

; constants
STACK_SIZE    equ 4096
KERN_BASE     equ 0xc0000000

; lower .text section
section .multiboot.text
start:
  ; set page table address
  mov ecx, page_table
  mov cr3, ecx

  ; enable 4MB page
  mov ecx, cr4
  or ecx, 0x00000010
  mov cr4, ecx

  ; enable paging
  mov ecx, cr0
  or ecx, 0x80000000
  mov cr0, ecx

  jmp hi_start

section .multiboot.data
align 4096
page_table:
  dd 0x00000083
  times ((KERN_BASE >> 22) - 1) dd 0
%assign i 0
%rep 1024 - (KERN_BASE >> 22) - 1
  dd 0x00000083 | i << 22
%assign i i+1
%endrep

; higher .text section
section .text
hi_start:
  ; setup stack
  mov esp, stack_top
  ; call c function
  call main

  cli
loop:
  hlt
  jmp loop

; .bss section
section .bss
stack_bottom:
  resb STACK_SIZE
stack_top:
