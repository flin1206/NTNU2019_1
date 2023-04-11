all: maze_stack.o test.c
	gcc maze_stack.o test.c -o test
	
maze_stack.o: maze_stack.c
	gcc -c maze_stack.c

clean:
	rm -f *.o test