CC = gcc
C_FLAGS = -Wall

all: minish unittest

logging.o: logging.c logging.h utils.h
	$(CC) $(C_FLAGS) -c $< -o $@

utils.o: utils.c utils.h
	$(CC) $(C_FLAGS) -c $< -o utils.o

lineparser.o: lineparser.c lineparser.h
	$(CC) $(C_FLAGS) -c $< -o $@

program.o: program.c program.h
	$(CC) $(C_FLAGS) -c $< -o $@

command.o: command.c command.h
	$(CC) $(C_FLAGS) -c $< -o $@

minish: minish.c lineparser.o program.o command.o logging.o utils.o
	$(CC) $(C_FLAGS) lineparser.o program.o command.o logging.o utils.o -o $@ $<
	@echo "Minish compilated successfully"

unittest: unittest.c utils.o lineparser.o command.o 
	gcc utils.o lineparser.o command.o -o $@ $<

clean:
	rm -f minish *.o

print:
	lpr *.c *.h