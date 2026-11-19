CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -Wall -Wextra -Werror -c \
         -Idrivers -Ilib -Ikernel

LDFLAGS = -T link.ld -melf_i386

ASFLAGS = -f elf

C_SOURCES = \
	kernel/kmain.c \
	kernel/interrupts/idt.c \
	drivers/framebuffer.c \
	lib/string.c

ASM_SOURCES = \
	arch/x86/loader.s \
	arch/x86/io.s \
	arch/x86/idt.s

C_OBJECTS = $(C_SOURCES:.c=.o)
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)


all: kernel.elf


kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@


os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	xorrisofs -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso


run: os.iso
	bochs -f bochsrc.txt -q


run-qemu: os.iso
	qemu-system-i386 -cdrom os.iso


%.o: %.c
	$(CC) $(CFLAGS) $< -o $@


%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


clean:
	rm -f \
		kernel/*.o \
		kernel/interrupts/*.o \
		drivers/*.o \
		lib/*.o \
		arch/x86/*.o \
		kernel.elf \
		os.iso