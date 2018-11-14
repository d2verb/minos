# toolchain prefix
#PFX=$(HOME)/opt/xv6-toolchain/bin/i386-elf-
PFX=

AS=nasm
ASFLAGS=-felf32

CC=$(PFX)gcc
CFLAGS=-m32 -ffreestanding -fno-common -fno-builtin -fomit-frame-pointer -fno-pic

LD=$(PFX)ld
LDFLAGS=-m elf_i386
