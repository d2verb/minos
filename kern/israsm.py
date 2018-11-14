print("bits 32")
print("extern isr_main\n")

print("section .text")
print("isr_common_stub:")
isr_common_stub = """\
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
"""
print(isr_common_stub)

for i in range(32):
    print("isr%d:" % i)
    print("  push byte 0")
    print("  push byte %d" % i)
    print("  jmp isr_common_stub")
    print()

print("section .data")
print("global isr_vectors")
print("isr_vectors:")
for i in range(32):
    print("  dd isr%d" % i)
