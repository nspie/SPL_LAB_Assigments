all: Task2b

Task2b: Task2b.o
	gcc -g -m32 -Wall -o Task2b Task2b.o


Task2b.o : Task2b.c
	gcc -m32 -g -Wall -c -o Task2b.o Task2b.c


.PHONY: clean 

clean: rm -f *.o Task2b
