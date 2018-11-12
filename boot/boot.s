[bits 32]
global start

extern main

; constants
STACK_SIZE equ 4096

; .text section
section .text
start:
  ; setup stack
  mov esp, stack_top

  ; call c function
  call main

loop:
  hlt
  jmp loop

; .bss section
section .bss
stack_bottom:
  resb STACK_SIZE
stack_top:
