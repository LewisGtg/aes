all: main

main: main.c aes.o
	gcc main.c aes.o -o main

aes.o: aes.c
	gcc -c aes.c -o aes.o