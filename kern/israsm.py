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

for i in range(256):
    print("isr%d:" % i)
    if i == 8 or (i >= 10 and i <= 14) or i == 17:
        print("  push %d" % i)
    else:
        print("  push 0")
        print("  push %d" % i)
    print("  jmp isr_common_stub")
    print()

print("section .data")
print("global isr_vectors")
print("isr_vectors:")
for i in range(256):
    print("  dd isr%d" % i)
