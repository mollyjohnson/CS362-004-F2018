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

	printf("TEST 1: game should end, three supply piles 0 but province cards not 0\n");	

	//NOTE: VALUE OF 1 = GAME OVER, VALUE OF 0 = GAME NOT OVER
	int i;
	int true = 1;
	int false = 0;
	for(i = 0; i < 27; i++)
	{
		testGame.supplyCount[i] = 0;
	}
	testGame.supplyCount[province] = 10;
	int isOver;
	isOver = isGameOver(&testGame);
	Assert(isOver == true,"3 supply piles 0 but province cards are not 0 test");
	printf("is game over: %d, expected: %d\n", isOver, true);
	
	memcpy(&testGame, &Game, sizeof(struct gameState));
	printf("TEST 2: game should end, province cards are 0 and 3 supply piles are not 0\n");
	for(i = 0; i < 27; i++)
	{
		testGame.supplyCount[i] = 5;
	}

	testGame.supplyCount[duchy] = 0;
	testGame.supplyCount[province] = 0;
	isOver = isGameOver(&testGame);
	Assert(isOver == true,"province cards are 0 and 3 supply piles are not test");
	printf("is game over: %d, expected: %d\n", isOver, true);

	memcpy(&testGame, &Game, sizeof(struct gameState));
	printf("TEST 3: game should not end, province cards are not 0 and supply piles at 0 isn't >= 3\n");

	//make 2 supply pile 0 to check for case where it ended the game any time even one supply pile was 0
	for(i = 0; i < 27; i++)
	{
		testGame.supplyCount[i] = 5;
	}	

	//only 2 supply piles are at 0
	testGame.supplyCount[duchy] = 0;
	testGame.supplyCount[smithy] = 0;
	isOver = isGameOver(&testGame);
	Assert(isOver == false,"province cards are 0 and 3 supply piles are not test");
	printf("is game over: %d, expected: %d\n", isOver, false);

	return 0;
}
