all: Task2a

Task2a: Task2a.o
	gcc -g -m32 -Wall -o Task2a Task2a.o


Task2a.o : Task2a.c
	gcc -m32 -g -Wall -c -o Task2a.o Task2a.c


.PHONY: clean 

clean: rm -f *.o Task2a
