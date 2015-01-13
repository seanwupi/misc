
all: sh xinetd

sh: sh.c sandbox.h
	gcc sh.c -o sh -static -O2
	strip sh

xinetd: xinetd.c sandbox.h
	gcc xinetd.c -o xinetd -static -O2
	strip xinetd

