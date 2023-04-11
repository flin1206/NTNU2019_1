all: stack.o test.c balance.c
	gcc test.c stack.o -o test
	gcc balance.c stack.o -o balance

stack.o: stack.h stack.c
	gcc -c stack.c

clean:
	rm -f *.o test