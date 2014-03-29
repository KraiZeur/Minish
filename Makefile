LIB=-lpthread

all: minish

minish: minish.c
	gcc -o minish minish.c

clean:
	rm *.o