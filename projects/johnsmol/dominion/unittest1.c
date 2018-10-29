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

#define FUNCTION_NAME "updateCoins"

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
	//create variables
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

	//27 card options plus one "error" option to make sure the program can handle case where
	//an invalid value has been passed in
	int cardType[] = { curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, 
			smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };
	
	char *cardTypeName[] = { "curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", 
			"smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map" };

	int cardCoinVal[] = { 0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4, };
	
	//test the getCard function directly
	int i;
	int returnVal;
	int errorVal = 1000;
	int correctErrorVal = -1;
	for(i = 0; i < 28; i++)
	{
		if (i == 27)
		{
			//test the return -1 default at end of function with an error number
			//that doesn't match any expected value
			printf("TEST %d: get card cost ERROR\n", i + 1);
			returnVal = getCost(errorVal);
			Assert(returnVal == correctErrorVal, "error card test");
			printf("card cost: %d, expected: %d\n", returnVal, correctErrorVal);

		}
		else
		{
			printf("TEST %d: get card cost %s\n", i + 1, cardTypeName[i]);
			returnVal = getCost(cardType[i]);
			Assert(returnVal == cardCoinVal[i], "get card cost test");
			printf("card cost: %d, expected: %d\n", returnVal, cardCoinVal[i]);
		}
	}

	return 0;
}
