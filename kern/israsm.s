[bits 32]
[extern isr_common]

section .text
isr_entry:
  pusha
  mov ax, ds
  push eax
  mov ax, 0x18
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call isr_common

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  popa
  add esp, 8
  iret

global isr0_entry
global isr1_entry
global isr2_entry
global isr3_entry
global isr4_entry
global isr5_entry
global isr6_entry
global isr7_entry
global isr8_entry
global isr9_entry
global isr10_entry
global isr11_entry
global isr12_entry
global isr13_entry
global isr14_entry
global isr15_entry
global isr16_entry
global isr17_entry
global isr18_entry
global isr19_entry
global isr20_entry
global isr21_entry
global isr22_entry
global isr23_entry
global isr24_entry
global isr25_entry
global isr26_entry
global isr27_entry
global isr28_entry
global isr29_entry
global isr30_entry
global isr31_entry

isr0_entry:
  push byte 0
  push byte 0
  jmp isr_entry

isr1_entry:
  push byte 0
  push byte 1
  jmp isr_entry

isr2_entry:
  push byte 0
  push byte 2
  jmp isr_entry

isr3_entry:
  push byte 0
  push byte 3
  jmp isr_entry

isr4_entry:
  push byte 0
  push byte 4
  jmp isr_entry

isr5_entry:
  push byte 0
  push byte 5
  jmp isr_entry

isr6_entry:
  push byte 0
  push byte 6
  jmp isr_entry

isr7_entry:
  push byte 0
  push byte 7
  jmp isr_entry

isr8_entry:
  push byte 0
  push byte 8
  jmp isr_entry

isr9_entry:
  push byte 0
  push byte 9
  jmp isr_entry

isr10_entry:
  push byte 0
  push byte 10
  jmp isr_entry

isr11_entry:
  push byte 0
  push byte 11
  jmp isr_entry

isr12_entry:
  push byte 0
  push byte 12
  jmp isr_entry

isr13_entry:
  push byte 0
  push byte 13
  jmp isr_entry

isr14_entry:
  push byte 0
  push byte 14
  jmp isr_entry

isr15_entry:
  push byte 0
  push byte 15
  jmp isr_entry

isr16_entry:
  push byte 0
  push byte 16
  jmp isr_entry

isr17_entry:
  push byte 0
  push byte 17
  jmp isr_entry

isr18_entry:
  push byte 0
  push byte 18
  jmp isr_entry

isr19_entry:
  push byte 0
  push byte 19
  jmp isr_entry

isr20_entry:
  push byte 0
  push byte 20
  jmp isr_entry

isr21_entry:
  push byte 0
  push byte 21
  jmp isr_entry

isr22_entry:
  push byte 0
  push byte 22
  jmp isr_entry

isr23_entry:
  push byte 0
  push byte 23
  jmp isr_entry

isr24_entry:
  push byte 0
  push byte 24
  jmp isr_entry

isr25_entry:
  push byte 0
  push byte 25
  jmp isr_entry

isr26_entry:
  push byte 0
  push byte 26
  jmp isr_entry

isr27_entry:
  push byte 0
  push byte 27
  jmp isr_entry

isr28_entry:
  push byte 0
  push byte 28
  jmp isr_entry

isr29_entry:
  push byte 0
  push byte 29
  jmp isr_entry

isr30_entry:
  push byte 0
  push byte 30
  jmp isr_entry

isr31_entry:
  push byte 0
  push byte 31
  jmp isr_entry
