#ifndef MICELI_CARDS_H
#define MICELI_CARDS_H

// DEFINES //
#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

#define PENALTY 0

#define CLUB 1
#define DIAMOND 2
#define HEART 3
#define SPADE 4

#define MAX_NAME 25

// STRUCTS //
struct card {
	int value; //holds the numeric value of the card for comparison
	int suit; //holds the suit value of the card for comparison
};

struct player {
	int score;
	int length;
	int val;
	int suit;
	char *id; //unique identifier for each player
};

// FUNCTIONS //
void flags(int err);
struct player *newPlayer();
void destroyPlayer(struct player *a);
int getNumPlayers(char *ch);
void pushChar(char ch, struct player *a);
void getName(struct player *a, int x);
void printCard(int value, int suit);
struct card **initDeck();
void shuffleDeck(struct card **deck);
void destroyDeck(struct card **deck);
void waitForInput();
struct player *takeTurn(struct player *p, int countCards, struct card **deck);
int checkWin(struct player *x, struct player *y);
void addWin(int winner, struct player *a, struct player *b);
int compare(int x, int y);
void displayWin(struct player *p);
void play2(struct player *p1, struct player *p2, struct card **deck);
void play3(struct player *p1, struct player *p2, struct player *p3, struct card **deck);
void play4(struct player *p1, struct player *p2, struct player *p3, struct player *p4, struct card **deck);

#endif