all: Task3

Task3: Task3.o
	gcc -g -m32 -Wall -o Task3 Task3.o


Task3.o : Task3.c
	gcc -m32 -g -Wall -c -o Task3.o Task3.c


.PHONY: clean 

clean: rm -f *.o Task3
