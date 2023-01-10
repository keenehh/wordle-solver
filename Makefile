CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g

all: wordle

wordle: solver.o wordle.o
	$(CC) solver.o wordle.o -o wordle

solver.o: solver.c
	$(CC) $(CFLAGS) -c solver.c

wordle.o: wordle.c
	$(CC) $(CFLAGS) -c wordle.c

clean:
	rm -f *.o wordle

format:
	clang-format -i -style=file *.[ch]


#testing stuff
