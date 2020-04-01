CC = gcc
CFLAGS = -Wall

all: cardwars

cardwars: miceli_cards.c
	$(CC) $(CFLAGS) miceli_cards.c -o cardwars

clean: 
	rm -f cardwars
