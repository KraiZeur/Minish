CC = gcc -Wall
LIB=-lpthread

all: minish

logging.o: logging.c logging.h utils.h
	$(CC) -c logging.c -o logging.o

utils.o: utils.c utils.h
	$(CC) -c utils.c -o utils.o

lineparser.o: lineparser.c lineparser.h
	$(CC) -c lineparser.c -o lineparser.o

program.o: program.c program.h
	$(CC) -c program.c -o program.o

command.o: command.c command.h
	$(CC) -c command.c -o command.o

minish: minish.c lineparser.o program.o command.o logging.o utils.o
	$(CC) lineparser.o program.o command.o logging.o utils.o -o minish minish.c

clean:
	rm *.o