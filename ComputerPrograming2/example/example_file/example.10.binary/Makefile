all: bmp_read_v1.c bmp_read_v2.c bmp_read_v2_error.c bmp_write.c
	gcc bmp_read_v1.c -o bmp_read_v1
	gcc bmp_read_v2.c -o bmp_read_v2
	gcc bmp_read_v2_error.c -o bmp_read_v2_error
	gcc bmp_write.c -o bmp_write
	gcc `pkg-config --cflags gtk+-3.0` -o gtest gtest.c `pkg-config --libs gtk+-3.0`
clean:
	rm -rf bmp_read_v1