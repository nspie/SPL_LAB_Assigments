all: lab3_mergesort

lab3_mergesort: lab3_mergesort.o
	gcc -g -m32 -Wall -o lab3_mergesort lab3_mergesort.o


lab3_mergesort.o : lab3_mergesort.c
	gcc -m32 -g -Wall -c -o lab3_mergesort.o lab3_mergesort.c


.PHONY: clean 

clean: rm -f *.o lab3_mergesort
