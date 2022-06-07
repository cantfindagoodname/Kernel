C_SRC = $(wildcard kernel/*.c drivers/*.c tools/*.c cpu/*.c shell/*.c app/*.c app/src/*.c)
HEADERS = $(wildcard include/*.h)

OBJ = $(C_SRC:.c=.o cpu/interrupt.o)

AS = nasm
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb

CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Iinclude/

EMULATOR = qemu-system-i386
BOOT = boot
KERNEL = kernel
ENTRY = kernel_entry
IMG = image

KERNEL_OFFSET = 0x1000

all: run

$(IMG).img: boot/$(BOOT).bin $(KERNEL).bin
	cat $^ > $@

$(KERNEL).bin: boot/$(ENTRY).o $(OBJ)
	$(LD) -o $@ --allow-multiple-definition -Ttext $(KERNEL_OFFSET) $^ --oformat binary

run: $(IMG).img
	qemu-img resize -f raw $< 128M
	$(EMULATOR) -drive file=$<,format=raw

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -ffreestanding -c $< -o $@

%.o: %.asm
	${AS} $< -f elf -o $@

%.bin: %.asm
	$(AS) -f bin $< -o $@

# Debug
$(KERNEL).elf: boot/$(ENTRY).o $(OBJ)
	$(LD) -o $@ --allow-multiple-definition -Ttext $(KERNEL_OFFSET) $^

debug: $(IMG).img $(KERNEL).elf
	qemu-img resize -f raw $< 256M
	$(EMULATOR) -s -S -drive file=$(IMG).img,format=raw &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL).elf"


.PHONY: clean
clean:
	@echo "Cleaning..."
	-@rm -f *.bin *.o *.img *.elf
	-@rm -f boot/*.bin boot/*.o kernel/*.o drivers/*.o tools/*.o cpu/*.o shell/*.o app/*.o app/src/*.o
