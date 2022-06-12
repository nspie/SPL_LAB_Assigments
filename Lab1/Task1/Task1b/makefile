all: 1b

1b: 1b.o
	gcc -g -m32 -Wall -o 1b 1b.o


1b.o : 1b.c
	gcc -m32 -g -Wall -c -o 1b.o 1b.c


.PHONY: clean 

clean: rm -f *.o 1b
