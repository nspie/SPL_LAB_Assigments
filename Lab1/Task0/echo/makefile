all: Target

Target: myEcho.o
	gcc -g -m32 -Wall -o Target myEcho.o


myEcho.o : myEcho.c
	gcc -m32 -g -Wall -c -o myEcho.o myEcho.c


.PHONY: clean 

clean: rm -f *.o Target
