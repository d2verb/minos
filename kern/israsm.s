bits 32
extern isr_main

section .text
isr_common_stub:
  pusha

  ; save old ds
  mov ax, ds
  push eax

  ; set kernel ds
  mov ax, 0x18
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call isr_main

  ; restore old ds
  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa

  ; clean stack pushed by `isrx`
  add esp, 8

  iret

isr0:
  push byte 0
  push byte 0
  jmp isr_common_stub

isr1:
  push byte 0
  push byte 1
  jmp isr_common_stub

isr2:
  push byte 0
  push byte 2
  jmp isr_common_stub

isr3:
  push byte 0
  push byte 3
  jmp isr_common_stub

isr4:
  push byte 0
  push byte 4
  jmp isr_common_stub

isr5:
  push byte 0
  push byte 5
  jmp isr_common_stub

isr6:
  push byte 0
  push byte 6
  jmp isr_common_stub

isr7:
  push byte 0
  push byte 7
  jmp isr_common_stub

isr8:
  push byte 0
  push byte 8
  jmp isr_common_stub

isr9:
  push byte 0
  push byte 9
  jmp isr_common_stub

isr10:
  push byte 0
  push byte 10
  jmp isr_common_stub

isr11:
  push byte 0
  push byte 11
  jmp isr_common_stub

isr12:
  push byte 0
  push byte 12
  jmp isr_common_stub

isr13:
  push byte 0
  push byte 13
  jmp isr_common_stub

isr14:
  push byte 0
  push byte 14
  jmp isr_common_stub

isr15:
  push byte 0
  push byte 15
  jmp isr_common_stub

isr16:
  push byte 0
  push byte 16
  jmp isr_common_stub

isr17:
  push byte 0
  push byte 17
  jmp isr_common_stub

isr18:
  push byte 0
  push byte 18
  jmp isr_common_stub

isr19:
  push byte 0
  push byte 19
  jmp isr_common_stub

isr20:
  push byte 0
  push byte 20
  jmp isr_common_stub

isr21:
  push byte 0
  push byte 21
  jmp isr_common_stub

isr22:
  push byte 0
  push byte 22
  jmp isr_common_stub

isr23:
  push byte 0
  push byte 23
  jmp isr_common_stub

isr24:
  push byte 0
  push byte 24
  jmp isr_common_stub

isr25:
  push byte 0
  push byte 25
  jmp isr_common_stub

isr26:
  push byte 0
  push byte 26
  jmp isr_common_stub

isr27:
  push byte 0
  push byte 27
  jmp isr_common_stub

isr28:
  push byte 0
  push byte 28
  jmp isr_common_stub

isr29:
  push byte 0
  push byte 29
  jmp isr_common_stub

isr30:
  push byte 0
  push byte 30
  jmp isr_common_stub

isr31:
  push byte 0
  push byte 31
  jmp isr_common_stub

isr32:
  push byte 0
  push byte 32
  jmp isr_common_stub

isr33:
  push byte 0
  push byte 33
  jmp isr_common_stub

isr34:
  push byte 0
  push byte 34
  jmp isr_common_stub

isr35:
  push byte 0
  push byte 35
  jmp isr_common_stub

isr36:
  push byte 0
  push byte 36
  jmp isr_common_stub

isr37:
  push byte 0
  push byte 37
  jmp isr_common_stub

isr38:
  push byte 0
  push byte 38
  jmp isr_common_stub

isr39:
  push byte 0
  push byte 39
  jmp isr_common_stub

isr40:
  push byte 0
  push byte 40
  jmp isr_common_stub

isr41:
  push byte 0
  push byte 41
  jmp isr_common_stub

isr42:
  push byte 0
  push byte 42
  jmp isr_common_stub

isr43:
  push byte 0
  push byte 43
  jmp isr_common_stub

isr44:
  push byte 0
  push byte 44
  jmp isr_common_stub

isr45:
  push byte 0
  push byte 45
  jmp isr_common_stub

isr46:
  push byte 0
  push byte 46
  jmp isr_common_stub

isr47:
  push byte 0
  push byte 47
  jmp isr_common_stub

section .data
global isr_vectors
isr_vectors:
  dd isr0
  dd isr1
  dd isr2
  dd isr3
  dd isr4
  dd isr5
  dd isr6
  dd isr7
  dd isr8
  dd isr9
  dd isr10
  dd isr11
  dd isr12
  dd isr13
  dd isr14
  dd isr15
  dd isr16
  dd isr17
  dd isr18
  dd isr19
  dd isr20
  dd isr21
  dd isr22
  dd isr23
  dd isr24
  dd isr25
  dd isr26
  dd isr27
  dd isr28
  dd isr29
  dd isr30
  dd isr31
  dd isr32
  dd isr33
  dd isr34
  dd isr35
  dd isr36
  dd isr37
  dd isr38
  dd isr39
  dd isr40
  dd isr41
  dd isr42
  dd isr43
  dd isr44
  dd isr45
  dd isr46
  dd isr47
