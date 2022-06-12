all: 1c

1c: 1c.o
	gcc -g -m32 -Wall -o 1c 1c.o


1c.o : 1c.c
	gcc -m32 -g -Wall -c -o 1c.o 1c.c


.PHONY: clean 

clean: rm -f *.o 1c
