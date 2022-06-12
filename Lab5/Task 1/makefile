all: Task1

Task1: Task1.o LineParser.o
	gcc -g -m32 -Wall -o Task1 Task1.o LineParser.o

Task1.o: Task1.c
	gcc -g -m32 -Wall -c -o Task1.o Task1.c

LineParser.o: LineParser.c
	gcc -g -m32 -Wall -c -o LineParser.o LineParser.c

.PHONY: clean

clean:
	rm -f *.o Task1
