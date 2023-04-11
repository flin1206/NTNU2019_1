all: upper_lower_api.o test.c
	gcc upper_lower_api.o test.c -o test
	
upper_lower_api.o: upper_lower_api.c
	gcc -c upper_lower_api.c -o upper_lower_api.o

clean:
	rm -rf *.o  test