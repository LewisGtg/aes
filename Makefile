all: main

main: main.c aes.o
	gcc main.c aes.o -o main

aes.o: aes.c
	gcc -c aes.c -o aes.o

testaOnetimepad: testaOnetimepad.c onetimepad.o
	gcc testaOnetimepad.c onetimepad.o -o testaOnetimepad -lm

onetimepad.o: onetimepad.c
	gcc -c onetimepad.c -o onetimepad.o