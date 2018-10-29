/*
Molly Johnson
OSU CS 362 Fall 2018
Assignment 3
Due: 10/28/18
unittest1.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//function declarations
void Assert(int expression, char* message);

#define FUNCTION_NAME "isGameOver"

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
This is the main function. Here the test variables will be declared/initialized,
the printf() and custom Assert functions will be called as needed to test the
program's behavior, and (prior to calling those functions), a replica gameState
and test gameState structure will be created for the test suite.
*/
int main()
{
	int numPlayers = 2;
	int currentPlayer = 0;
	int otherPlayer = 1;
	int handPos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	//seed used to get game randomness
	int seed = 1000;
	//create a game state and a test game state
	struct gameState Game, testGame;
	//10 "action" cards are allowed per game (tho these can differ per game). are 27 options total in this version
	//of dominion, but you're only allowed 10 per game so only 10 will be tested in this test suite
	int kingdomCards[10] = { smithy, adventurer, village, baron, minion, great_hall, council_room, steward, gardens, mine };

	
	//initialize the game with the given num of players and variables
	initializeGame(numPlayers, kingdomCards, seed, &Game);

	printf("------------------------- Testing function: %s -------------------------\n", FUNCTION_NAME);	
	
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));


	return 0;
}
