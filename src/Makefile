CC = gcc
C_FLAGS = -Wall

all: minish unittest

logging.o: logging.c logging.h utils.h
	$(CC) $(C_FLAGS) -c logging.c -o $@

utils.o: utils.c utils.h
	$(CC) $(C_FLAGS) -c utils.c -o utils.o

lineparser.o: lineparser.c lineparser.h
	$(CC) $(C_FLAGS) -c lineparser.c -o $@

program.o: program.c program.h
	$(CC) $(C_FLAGS) -c program.c -o $@

command.o: command.c command.h
	$(CC) $(C_FLAGS) -c command.c -o $@

minish: minish.c lineparser.o program.o command.o logging.o utils.o
	$(CC) $(C_FLAGS) lineparser.o program.o command.o logging.o utils.o -o $@ minish.c
	@echo "Minish compilated successfully"

unittest: utils.o lineparser.o command.o unittest.c
	gcc utils.o lineparser.o command.o -o $@ unittest.c

clean:
	rm *.o
	rm minish