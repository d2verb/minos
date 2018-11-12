[bits 32]
global start

extern main

; constants
STACK_SIZE equ 4096

; .text section
section .text
start:
  ; setup stack
  mov esp, stack + STACK_SIZE - 4

  ; call c function
  call main

loop:
  hlt
  jmp loop

; .bss section
section .bss
  stack resb STACK_SIZE
