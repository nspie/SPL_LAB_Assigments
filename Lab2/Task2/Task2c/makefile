all: Task2c

Task2c: Task2c.o
	gcc -g -m32 -Wall -o Task2c Task2c.o


Task2c.o : Task2c.c
	gcc -m32 -g -Wall -c -o Task2c.o Task2c.c


.PHONY: clean 

clean: rm -f *.o Task2c
