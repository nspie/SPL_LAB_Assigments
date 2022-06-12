all: mypipe

mypipe: mypipe.o LineParser.o
	gcc -m32 -g -Wall -o mypipe mypipe.o LineParser.o

mypipe.o: mypipe.c
	gcc -g -Wall -m32  -c -o mypipe.o mypipe.c

LineParser.o: LineParser.c
	gcc -g -m32 -Wall -c -o LineParser.o LineParser.c

.PHONY: clean

clean: 
	rm -f *.o mypipe
