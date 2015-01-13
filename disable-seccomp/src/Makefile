all: 
	nasm -o core.o core.asm -felf32
	gcc -o launcher launcher.c core.o -m32 -zexecstack
	nasm -o core64.o core64.asm -felf64
	gcc -o launcher64 launcher.c core64.o -zexecstack

	nasm -o test.o test.asm -felf32
	ld -o test test.o -melf_i386
	objcopy -O binary test test.bin

	nasm -o test64.o test64.asm -felf64
	ld -o test64 test64.o 
	objcopy -O binary test64 test64.bin


