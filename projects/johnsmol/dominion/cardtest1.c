/*
Molly Johnson
OSU CS 362 Fall 2018
Assignment 3
Due: 10/28/18
cardtest1.c
Some setup and general method for creating test game state, etc adapted from the
cardtest4.c steward example file provided in the OSU CS 362 Fall 2018 lectures.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "smithy"

//function declarations
void Assert(int expression, char* message);

/*

custom assert expression adapted from:
https://www.tutorialspoint.com/c_standard_library/assert_h.htm
*/
void Assert(int expression, char* message)
{
	if(expression == 0)
	{
		printf("for %s: ", message);
		printf("TEST FAILED\n");
	}
	else
	{
		printf("for %s: ", message);
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}
}

/*

*/
int main()
{
	//create variables
	int newCards = 0;
	int discardedCards = 1;
	int extraCoins = 0;
	int shuffledCards = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int otherPlayer = 1;
	int handPos = 0;
	int choice1 = 0;
	int choice2 = 2;
	int choice3 = 0;
	int bonus = 0;
	int remove1, remove2;
	//seed used to get game randomness
	int seed = 1000;
	//create a game state and a test game state
	struct gameState Game, testGame;
	//10 "action" cards are allowed per game (tho these can differ per game)
	int actionCards[10] = { smithy, adventurer, village, baron, minion, great_hall, council_room, steward, gardens, mine };

	//initialize the game with the given num of players and variables
	initializeGame(numPlayers, actionCards, seed, &Game);

	printf("------------------------- Testing card: %s -------------------------\n", TESTCARD); 
	printf("TEST 1: current player receives 3 cards\n");

	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	newCards = 3;
	Assert(testGame.handCount[currentPlayer] == (Game.handCount[currentPlayer] + newCards -discardedCards), "hand count test");
	printf("hand count: %d, expected: %d\n", testGame.handCount[currentPlayer],Game.handCount[currentPlayer] + newCards -discardedCards); 
	//reset any changed variables
	newCards = 0;

	printf("TEST 2: 3 cards come from the current player's deck\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	discardedCards = 3;
	Assert(testGame.deckCount[currentPlayer] == (Game.deckCount[currentPlayer] - discardedCards), "deck count test"); 
	printf("deck count: %d, expected: %d\n", testGame.deckCount[currentPlayer], Game.deckCount[currentPlayer] - discardedCards);
	//reset any changed variables
	discardedCards = 1;

	printf("TEST 3: discard pile gains 1 card\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.discardCount[currentPlayer] == (Game.discardCount[currentPlayer] + discardedCards), "discard pile test");
	printf("discard count: %d, expected: %d\n", testGame.discardCount[currentPlayer], Game.discardCount[currentPlayer] + discardedCards);

	printf("TEST 4: no state change for other players(hand count, deck count, discard count)\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.handCount[otherPlayer] == (Game.handCount[otherPlayer]), "other player hand count test");
	printf("other player hand count: %d, expected: %d\n", testGame.handCount[otherPlayer],Game.handCount[otherPlayer]); 
	Assert(testGame.deckCount[otherPlayer] == (Game.deckCount[otherPlayer]), "other player deck count test"); 
	printf("other player's deck count: %d, expected: %d\n", testGame.deckCount[otherPlayer], Game.deckCount[otherPlayer]);
	Assert(testGame.discardCount[otherPlayer] == (Game.discardCount[otherPlayer]), "other player discard pile test");
	printf("other player discard count: %d, expected: %d\n", testGame.discardCount[otherPlayer], Game.discardCount[otherPlayer]);




	return 0;
}
