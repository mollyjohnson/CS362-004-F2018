/*
Molly Johnson
OSU CS 362 Fall 2018
Assignment 3
Due: 10/28/18
cardtest2.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define TESTCARD "village"

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
		printf("%s: ", message);
		printf("TEST FAILED\n");
	}
	else
	{
		printf("%s: ", message);
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
	//10 "action" cards are allowed per game (tho these can differ per game). are 27 options total in this version
	//of dominion, but you're only allowed 10 per game so only 10 will be tested in this test suite
	int kingdomCards[10] = { smithy, adventurer, village, baron, minion, great_hall, council_room, steward, gardens, mine };

	//initialize the game with the given num of players and variables
	initializeGame(numPlayers, kingdomCards, seed, &Game);

	printf("------------------------- Testing card: %s -------------------------\n", TESTCARD);
	printf("TEST 1: current player receives 1 card \n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
	newCards = 1;
	Assert(testGame.handCount[currentPlayer] == (Game.handCount[currentPlayer] + newCards -discardedCards), "hand count test");
	printf("hand count: %d, expected: %d\n", testGame.handCount[currentPlayer],Game.handCount[currentPlayer] + newCards -discardedCards);
	//reset any changed variables
	newCards = 0;
	




	return 0;
}
