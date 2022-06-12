all: Task2

Task2: Task2.o
	gcc -g -m32 -Wall -o Task2 Task2.o


Task2.o : Task2.c
	gcc -m32 -g -Wall -c -o Task2.o Task2.c


.PHONY: clean 

clean: rm -f *.o Task2
