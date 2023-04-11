CFLAGS = -O3 -Wall
INCLUDE = -I curl-7.63.0/include
LIB = -L curl-7.63.0/lib/.libs/

all: opendata.c
	gcc ${CFLAGS} ${INCLUDE} ${LIB} opendata.c -o opendata -lcurl

clean:
	rm -f opendata