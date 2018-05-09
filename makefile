all: pa4 main

pa4: pa4.c pa4.h makefile
	gcc -g -c pa4.c
	ar rc libpa4.a pa4.o

main: main.c libpa4.a makefile
	gcc -Wall -g -o main main.c libpa4.a

clean:
	rm -rf main *.o
