all: 2b

2b: 2b.o LineParser.o
	gcc -g -m32 -Wall -o 2b 2b.o LineParser.o

2b.o: 2b.c
	gcc -g -m32 -Wall -c -o 2b.o 2b.c

LineParser.o: LineParser.c
	gcc -g -m32 -Wall -c -o LineParser.o LineParser.c

.PHONY: clean

clean:
	rm -f *.o 2b
