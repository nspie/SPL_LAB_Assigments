all: 2a

2a: 2a.o LineParser.o
	gcc -g -m32 -Wall -o 2a 2a.o LineParser.o

2a.o: 2a.c
	gcc -g -m32 -Wall -c -o 2a.o 2a.c

LineParser.o: LineParser.c
	gcc -g -m32 -Wall -c -o LineParser.o LineParser.c

.PHONY: clean

clean:
	rm -f *.o 2a
