all: gtest.c
	gcc `pkg-config --cflags gtk+-3.0` -o gtest gtest.c `pkg-config --libs gtk+-3.0`
clean:
	rm -rf gtest
