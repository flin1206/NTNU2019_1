all: queue.o test.c 
	gcc test.c queue.o -o test

queue.o: queue.h queue.c
	gcc -c queue.c

clean:
	rm -f *.o test