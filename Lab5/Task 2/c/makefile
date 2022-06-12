all: Task2

Task2: Task2.o LineParser.o
	gcc -g -m32 -Wall -o Task2 Task2.o LineParser.o

Task2.o: Task2.c
	gcc -g -m32 -Wall -c -o Task2.o Task2.c

LineParser.o: LineParser.c
	gcc -g -m32 -Wall -c -o LineParser.o LineParser.c

.PHONY: clean

clean:
	rm -f *.o Task2
