CC = gcc
CFLAGS = -Wall

all: memgrind

memgrind: card_grind.c testcard
	$(CC) $(CFLAGS) card_grind.c -o memgrind

testcard: card_grind_test.c 
	$(CC) $(CFLAGS) card_grind_test.c -o testcard

clean:
	rm -f memgrind
	rm -f testcard