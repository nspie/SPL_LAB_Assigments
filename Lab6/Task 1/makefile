all: mypipeshell

mypipeshell: mypipeshell.o LineParser.o
	gcc -m32 -g -Wall -o mypipeshell mypipeshell.o LineParser.o

mypipeshell.o: mypipeshell.c
	gcc -g -Wall -m32  -c -o mypipeshell.o mypipeshell.c

LineParser.o: LineParser.c
	gcc -g -m32 -Wall -c -o LineParser.o LineParser.c

.PHONY: clean

clean: 
	rm -f *.o mypipeshell
