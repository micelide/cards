#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "miceli_cards.h"

/** * * * * * * * * * * * F U N C T I O N S * * * * * * * * * * * **/
void flags(int err)
{ 
	if(err == 0) { printf("Invalid number of players, please try again with 2, 3, or 4\n"); }
	else if(err == 1) { printf("Please enter a name for each player\n"); }
	else if(err == 2) { printf("Players must have unique names\n"); }
	else if(err == 3) { printf("Please run the game without any additional arguments\n"); }
	
}
struct player *newPlayer()
{//create a player
	struct player *new = malloc(sizeof(struct player));
	new->length = 0;
	new->score = 0;
	new->val = -1;
	new->suit = -1;
	new->id = malloc(sizeof(MAX_NAME));
	return new;
}
void destroyPlayer(struct player *a)
{
	free(a->id);
	free(a);
}
int getNumPlayers(char *ch)
{//get the user's input
	int count = 0;
	printf("Enter the number of Players\n");
	while( (ch[count] = getchar()) != EOF)
	{
		if(ch[count] == '\n') { break; }
		else if(count > 2) { return 0; } //ensures we don't go out of bounds
		++count;
	}
	if(ch[0] == '2') { return 2; }
	else if(ch[0] == '3') { return 3; }
	else if(ch[0] == 4) { return 4; }
	return 0;
}
void pushChar(char ch, struct player *a)
{//add char to the string
	if( (a->length%MAX_NAME == 0)&&(a->length > 0) )
	{//check if we need to reallocate memory for the ID
		a->id = realloc(a->id, a->length+MAX_NAME+1);
	}
	//add the char to the ID & move the pointer
	a->id[a->length] = ch;
	a->length++;
}
void getName(struct player *a, int x)
{//populate the string using pushChar
	char ch;
	printf("Enter the name of player %d: \n", x);
	while((ch = getchar()) != EOF)
	{
		if( (ch == '\n')&&(a->length > 0) ) { break; }
		pushChar(ch, a);
	}
}
void printCard(int value, int suit)
{
	//get the suit name
 	char *suitname;
 	if(suit == CLUB) { suitname = "club"; }
 	else if(suit == DIAMOND) { suitname = "diamond"; }
 	else if (suit == HEART) { suitname = "heart"; }
 	else { suitname = "spade"; }

 	if( (value > 0)&&(value < 11) )
 	{ //for cards with value equal to the display value
 		printf(" - - - - - - - -\n");
		printf("|\t\t|\n");
		printf("|\t\t|\n");
		printf("|\t%d\t|\n", value);
		printf("|\t\t|\n");
		printf("|    %s\t|\n", suitname);
		printf("|\t\t|\n");
		printf("|\t\t|\n");
		printf(" - - - - - - - -\n");
 	}
 	else 
 	{ //for cards with value equal to a certain name i.e. value of 11 = jack
 		char *valname;
 		if(value == JACK) { valname = "jack"; }
 		else if(value == QUEEN) { valname = "queen"; }
 		else if (value == KING) { valname = "king"; }
 		else if (value == ACE) { valname = "ace"; }
 		else { valname = "penalty"; }
 		printf(" - - - - - - - -\n");
		printf("|\t\t|\n");
		printf("|\t\t|\n");
		printf("|    %s\t|\n", valname);
		printf("|\t\t|\n");
		printf("|    %s\t|\n", suitname);
		printf("|\t\t|\n");
		printf("|\t\t|\n");
		printf(" - - - - - - - -\n");
 	}
	
}
struct card **initDeck() 
{ //initializes the deck in order of suit & face value
	struct card **deck = malloc(55 * sizeof(struct card*));
	for(int i = 0; i < 56; i++)
	{
		deck[i] = malloc(sizeof(struct card));
	}

	int placeholder = 0; //keep track of the array index
	for(int j = 1; j < 5; j++)
	{
		for(int i = 2; i < 16; i++)
		{
			if(i == 15) { deck[placeholder]->value = PENALTY; }
			else { deck[placeholder]->value = i; }

			deck[placeholder]->suit = j;

			++placeholder;
		}
	}
	return deck;
}
void shuffleDeck(struct card **deck)
{//shuffles the deck
	struct card *ptr1 = malloc(sizeof(struct card)); 
	srand(time(0)); 
	for(int i = 0; i < 56; i++)
	{//loop through all cards in the deck
		//save the current value
		ptr1 = deck[i];
		//generate a random number card
		int random = (rand() % 56); 
		//swap the current card with the random card
		deck[i] = deck[random];
		deck[random] = ptr1;
	}
}
void destroyDeck(struct card **deck)
{
	for(int i = 0; i < 56; i++)
	{
		free(deck[i]);
	}
	free(deck);
}
void waitForInput()
{//wait for user to push 'ENTER'
	char ch;

	printf("Press 'ENTER' to take your turn\n");
	while((ch = getchar()) != EOF)
	{
		if(ch == '\n') { break; }
		continue;
	}
}
struct player *takeTurn(struct player *p, int countCards, struct card **deck)
{ //wait for 'ENTER', draw the top card from the deck and add it to the player's hand, then add a penalty if needed
	waitForInput();
	p->val = deck[countCards]->value;
	p->suit = deck[countCards]->suit;
	printCard(deck[countCards]->value, deck[countCards]->suit);
	if(p->val == 0) 
	{ 
		printf("It's the penalty card!\n");
		if(p->score > 0)
		{
			p->score--;
		}
		else 
		{
			printf("Score is already 0\n");
		}
	}
	return p;
}
int checkWin(struct player *x, struct player *y)
{//return the player holding the higher card
	if(x->val > y->val) { return 1;}
	else if(x->val < y->val) { return 2; }
	else
	{
		if(x->suit > y->suit) { return 1; }
		else { return 2; }
	}
}
void addWin(int winner, struct player *a, struct player *b)
{//modify score of the winner
	if(winner == 1) { a->score += 2; }
	else { b->score += 2; }
}
int compare(int x, int y)
{//check for a win (score >= 21)&&(lead by 2 points)
	if( (x > 20)&&(x >= (y+2)) ) { return 1; }
	else if( (y > 20)&&(y >= (x+2)) ) { return 2; }
	return 0;
}
void displayWin(struct player *p)
{
	printf("***...**..*.. .  The winner is  . ..*..**...***\n");
	printCard(p->val, p->suit);
	printf("Congratulations Player %s\n", p->id);
}
void play2(struct player *p1, struct player *p2, struct card **deck)
{//play the game with 2 players
	shuffleDeck(deck);
	int countCards = 0;
	int winner = 0;
	char wflag = 'n';
	//player 1 takes their turn
	printf("Player %s\n", p1->id);
	p1 = takeTurn(p1, countCards, deck);
	//go to the next card
	++countCards;
	//player 2 takes their turn
	printf("Player %s\n", p2->id);
	p2 = takeTurn(p2, countCards, deck);
	//go to the next card
	++countCards;
	//find the winner and adjust score
	winner = checkWin(p1, p2);
	if(winner == 1) { displayWin(p1); }
	else { displayWin(p2); }
	addWin(winner, p1, p2);
	winner = 0; //reset
	printf("***...**..*.. .  Score Board  . ..*..**...***\n");
	printf("Player %s \t%d\n", p1->id, p1->score);
	printf("Player %s \t%d\n", p2->id, p2->score);
	if( (p1->score > 20)||(p2->score > 20) )
	{ //if the players have at least 21, check for a 2 point lead
		winner = compare(p1->score, p2->score);
		if(winner != 0) 
		{ 
			wflag = 'y';
			printf("Congratulations! That's game\n");
		}
		else
		{//start the game over with a new deck
			printf("End of round reached without a winner, reshuffling to continue...\n");
			play2(p1, p2,deck);
		}
	}
	else
	{//start the game over with a new deck
		printf("End of round reached without a winner, reshuffling to continue...\n");
		play2(p1, p2,deck);
	}
}
void play3(struct player *p1, struct player *p2, struct player *p3, struct card **deck)
{//play the game with 3 players
	shuffleDeck(deck);
	int countCards = 0;
	int winner12 = 0;
	int winner3 = 0;
	char wflag = 'n';
	//player 1 takes their turn
	printf("Player %s\n", p1->id);
	p1 = takeTurn(p1, countCards, deck);
	//go to the next card
	++countCards;
	//player 2 takes their turn
	printf("Player %s\n", p2->id);
	p2 = takeTurn(p2, countCards, deck);
	//go to the next card
	++countCards;

	printf("Player %s\n", p3->id);
	p3 = takeTurn(p3, countCards, deck);
	++countCards;
	//find the winner and adjust score
	winner12 = checkWin(p1, p2);
	if(winner12 == 1)
	{
		winner3 = checkWin(p1,p3);
		if(winner3 == 1) { displayWin(p1); }
		else { displayWin(p3); }
		addWin(winner3, p1, p3);
	}
	else
	{
		winner3 = checkWin(p2,p3);
		if(winner3 == 1) { displayWin(p2); }
		else { displayWin(p3); }
		addWin(winner3, p2, p3);
	}
	printf("***...**..*.. .  Score Board  . ..*..**...***\n");
	printf("Player %s \t%d\n", p1->id, p1->score);
	printf("Player %s \t%d\n", p2->id, p2->score);
	printf("Player %s \t%d\n", p3->id, p3->score);
	winner3 = 0; //reset
	//check for end of game -- score 21 or more with a 2 point lead
	if( (p1->score > 20)||(p2->score > 20)||(p3->score > 20) )
	{//compare 1 & 2..then compare the higher player with 3
		winner12 = compare(p1->score, p2->score);
		if(winner12 == 1) { winner3 = compare(p1->score, p3->score); }
		else if(winner12 == 2) { winner3 = compare(p2->score, p3->score); }
		else
		{
			winner12 = compare(p1->score, p3->score);
			if(winner12 != 0) { winner3 = compare(p2->score, p3->score); }
			else { winner3 = 0; } //no need to call the function again
		}
		if(winner3 != 0) 
		{ 
			wflag = 'y';
			printf("Congratulations! That's game\n");
		}
		else
		{//start the game over with a new deck
			printf("End of round reached without a winner, reshuffling to continue...\n");
			play3(p1, p2, p3,deck);
		}
	}
	else
	{//start the game over with a new deck
		printf("End of round reached without a winner, reshuffling to continue...\n");
		play3(p1, p2, p3,deck);
	}
}
void play4(struct player *p1, struct player *p2, struct player *p3, struct player *p4, struct card **deck)
{//play the game with four players
	shuffleDeck(deck);
	int countCards = 0;
	int winner12 = 0;
	int winner34 = 0;
	int winner = 0;
	char wflag = 'n';
	//player 1 takes their turn
	printf("Player %s\n", p1->id);
	p1 = takeTurn(p1, countCards, deck);
	//go to the next card
	++countCards;
	//player 2 takes their turn
	printf("Player %s\n", p2->id);
	p2 = takeTurn(p2, countCards, deck);
	//go to the next card
	++countCards;
	//player 3 takes their turn
	printf("Player %s\n", p3->id);
	p3 = takeTurn(p3, countCards, deck);
	++countCards;
	//player 4 takes their turn
	printf("Player %s\n", p4->id);
	p4 = takeTurn(p4, countCards, deck);
	++countCards;
	//find the winner and adjust score
	winner12 = checkWin(p1, p2);
	winner34 = checkWin(p3,p4);
	if( (winner12 == 1)&&(winner34 == 1) )
	{
		winner = checkWin(p1,p3);
		if(winner == 1) { displayWin(p1); }
		else { displayWin(p3); }
		addWin(winner, p1, p3);
	}
	else if( (winner12 == 1)&&(winner34 == 2) )
	{
		winner = checkWin(p1,p4);
		if(winner == 1) { displayWin(p1); }
		else { displayWin(p4); }
		addWin(winner, p1, p4);
	}
	else if( (winner12 == 2)&&(winner34 == 1) )
	{
		winner = checkWin(p2,p3);
		if(winner == 1) { displayWin(p2); }
		else { displayWin(p3); }
		addWin(winner, p2,p3);
	}
	else
	{
		winner = checkWin(p2,p4);
		if(winner == 1) { displayWin(p2); }
		else { displayWin(p4); }
		addWin(winner, p2,p4);
	}
	printf("***...**..*.. .  Score Board  . ..*..**...***\n");
	printf("Player %s \t%d\n", p1->id, p1->score);
	printf("Player %s \t%d\n", p2->id, p2->score);
	printf("Player %s \t%d\n", p3->id, p3->score);
	printf("Player %s \t%d\n", p4->id, p4->score);
	winner = 0; //reset
	//check for end of game
	if( (p1->score > 20)||(p2->score > 20)||(p3->score > 20)||(p4->score > 20) )
	{//compare 1 & 2..then compare the higher player with 3
		winner12 = compare(p1->score, p2->score);
		winner34 = compare(p3->score, p4->score);
		if( (winner12 == 1)&&(winner34 == 1) ) { winner = compare(p1->score, p3->score); }
		else if( (winner12 == 1)&&(winner34 == 2) ) { winner = compare(p1->score, p4->score); }
		else if( (winner12 == 2)&&(winner34 == 1) ) { winner = compare(p2->score, p3->score);}
		else { winner = compare(p2->score, p4->score); }
		if(winner != 0) 
		{ 
			wflag = 'y';
			//break;
			printf("Congratulations! That's game\n");
		}
		else
		{
			printf("End of round reached without a winner, reshuffling to continue...\n");
			play4(p1, p2, p3, p4,deck);
		}
	}
	else
	{
		printf("End of round reached without a winner, reshuffling to continue...\n");
		play4(p1, p2, p3, p4,deck);
	}
}
/** * * * * * * * * * * * * * * M A I N * * * * * * * * * * * * * * **/
int main(int argc, char **argv)
{
	if(argc > 1) 
	{//if an argument is passed, error. could interfere with the number of players, player names, etc
		flags(3);
		return 0;
	}
	// BEGIN //
	printf("***...**..*.. .  WELCOME TO CARD WARS!  . ..*..**...***\n");
	char *temp = malloc(sizeof(MAX_NAME));
	int numplayers = getNumPlayers(temp);
	if(numplayers == 0)
	{//user gave invalid input
		flags(0);
		return 0;
	}
	free(temp);
	//set up deck
	struct card **deck = initDeck();
	//create the players according to the number given
	struct player *p1 = newPlayer();
	getName(p1, 1);
	struct player *p2 = newPlayer();
	getName(p2, 2);
	if(strcmp(p1->id, p2->id) == 0)
	{//if the names are not unique, we have an error
		flags(2);
		return 0;
	}
	if(numplayers > 2)
	{//if the user specified 3 or 4, we need to create additional players (1 & 2 are default)
		struct player *p3 = newPlayer();
		getName(p3, 3);
		if( (strcmp(p1->id, p3->id) == 0)||(strcmp(p2->id, p3->id) == 0) )
		{//nonunqiue names, error
			flags(2);
			return 0;
		}
		if(numplayers == 4)
		{//we have 4 players
			struct player *p4 = newPlayer();
			getName(p4, 4);
			if( (strcmp(p1->id, p4->id) == 0)||(strcmp(p2->id, p4->id) == 0)||(strcmp(p3->id, p4->id) == 0) )
			{//nonunqiue names, error
				flags(2);
				return 0;
			}
			//play
			play4(p1,p2,p3,p4,deck);
			//once the game is finished, clean up the memory
			destroyPlayer(p4);
		}
		else
		{ //play
			play3(p1,p2,p3,deck); 
		}
		//game is finished, clean up
		destroyPlayer(p3);
	}
	else 
	{ //play
		play2(p1,p2,deck); 
	}
	//game is finished, clean up
	destroyPlayer(p1);
	destroyPlayer(p2);
	destroyDeck(deck);
	return 0; //done
}