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

#define FUNCTION_NAME "handCard"

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

	int handCardIndex = handCard(handPos, &testGame);

	printf("TEST 1: current player's hand at handPos 0\n");
	Assert(handCardIndex == Game.hand[currentPlayer][handPos], "hand card test");
	printf("hand card index: %d, expected: %d\n", handCardIndex, Game.hand[currentPlayer][handPos]);

	//since gameState struct was passed into function, check that all game states for both players are not chnaged,
	//and kingdom and victory card piles are not changed.
	printf("TEST 2: current player hand card count doesn't change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.handCount[currentPlayer] == (Game.handCount[currentPlayer]), "hand count test");
	printf("hand count: %d, expected: %d\n", testGame.handCount[currentPlayer],Game.handCount[currentPlayer]);

	printf("TEST 3: no  cards come from the current player's deck\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.deckCount[currentPlayer] == (Game.deckCount[currentPlayer]), "deck count test");
	printf("deck count: %d, expected: %d\n", testGame.deckCount[currentPlayer], Game.deckCount[currentPlayer]);

	printf("TEST 4: discard pile stays the same\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.discardCount[currentPlayer] == (Game.discardCount[currentPlayer]), "discard pile test");
	printf("discard count: %d, expected: %d\n", testGame.discardCount[currentPlayer], Game.discardCount[currentPlayer]);

	printf("TEST 5: no state change for things specific to other players (hand count, deck count, discard count\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.handCount[otherPlayer] == (Game.handCount[otherPlayer]), "other player hand count test");
	printf("other player hand count: %d, expected: %d\n", testGame.handCount[otherPlayer],Game.handCount[otherPlayer]);
	Assert(testGame.deckCount[otherPlayer] == (Game.deckCount[otherPlayer]), "other player deck count test");
	printf("other player's deck count: %d, expected: %d\n", testGame.deckCount[otherPlayer], Game.deckCount[otherPlayer]);
	Assert(testGame.discardCount[otherPlayer] == (Game.discardCount[otherPlayer]), "other player discard pile test");
	printf("other player discard count: %d, expected: %d\n", testGame.discardCount[otherPlayer], Game.discardCount[otherPlayer]);

	printf("TEST 6: no state change to victory card piles\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	//kingdomcards in this game
	//int kingdomCards[10] = { smithy, adventurer, village, baron, minion, great_hall, council_room, steward, gardens, mine };
	Assert(testGame.supplyCount[smithy] == Game.supplyCount[smithy], "kingdom card smithy test");
	printf("kingdom card smithy count: %d, expected: %d\n",testGame.supplyCount[smithy],Game.supplyCount[smithy]); 
	Assert(testGame.supplyCount[adventurer] == Game.supplyCount[adventurer], "kingdom card adventurer test");
	printf("kingdom card adventurer count: %d, expected: %d\n",testGame.supplyCount[adventurer],Game.supplyCount[adventurer]); 
	Assert(testGame.supplyCount[village] == Game.supplyCount[village], "kingdom card village test");
	printf("kingdom card village count: %d, expected: %d\n",testGame.supplyCount[village],Game.supplyCount[village]); 
	Assert(testGame.supplyCount[baron] == Game.supplyCount[baron], "kingdom card baron test");
	printf("kingdom card baron count: %d, expected: %d\n",testGame.supplyCount[baron],Game.supplyCount[baron]); 
	Assert(testGame.supplyCount[minion] == Game.supplyCount[minion], "kingdom card minion test");
	printf("kingdom card minion count: %d, expected: %d\n",testGame.supplyCount[minion],Game.supplyCount[minion]); 
	Assert(testGame.supplyCount[great_hall] == Game.supplyCount[great_hall], "kingdom card great_hall test");
	printf("kingdom card great_hall count: %d, expected: %d\n",testGame.supplyCount[great_hall],Game.supplyCount[great_hall]); 
	Assert(testGame.supplyCount[council_room] == Game.supplyCount[council_room], "kingdom card council_room test");
	printf("kingdom card council_room count: %d, expected: %d\n",testGame.supplyCount[council_room],Game.supplyCount[council_room]); 
	Assert(testGame.supplyCount[steward] == Game.supplyCount[steward], "kingdom card steward test");
	printf("kingdom card steward count: %d, expected: %d\n",testGame.supplyCount[steward],Game.supplyCount[steward]); 
	Assert(testGame.supplyCount[gardens] == Game.supplyCount[gardens], "kingdom card gardens test");
	printf("kingdom card gardens count: %d, expected: %d\n",testGame.supplyCount[gardens],Game.supplyCount[gardens]); 
	Assert(testGame.supplyCount[mine] == Game.supplyCount[mine], "kingdom card mine test");
	printf("kingdom card mine count: %d, expected: %d\n",testGame.supplyCount[mine],Game.supplyCount[mine]); 
	
	printf("TEST 7: no state change to kingdom card piles\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);Assert(testGame.supplyCount[estate] == Game.supplyCount[estate], "victory card estate test");
	printf("victory card estate count: %d, expected: %d\n",testGame.supplyCount[estate],Game.supplyCount[estate]); 
	Assert(testGame.supplyCount[duchy] == Game.supplyCount[duchy], "victory card duchy test");
	printf("victory card duchy count: %d, expected: %d\n",testGame.supplyCount[duchy],Game.supplyCount[duchy]); 
	Assert(testGame.supplyCount[province] == Game.supplyCount[province], "victory card province test");
	printf("victory card province count: %d, expected: %d\n",testGame.supplyCount[province],Game.supplyCount[province]); 

	printf("TEST 8: played card pile  stays the same\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.playedCardCount == (Game.playedCardCount), "played card pile test");
	printf("played card count count: %d, expected: %d\n", testGame.playedCardCount, Game.playedCardCount);

	printf("TEST 9: numPlayers does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.numPlayers == Game.numPlayers, "other player hand count test");
	printf("num players: %d, expected: %d\n", testGame.numPlayers, Game.numPlayers);

	printf("TEST 10: embargoTokens does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.embargoTokens[choice1] == Game.embargoTokens[choice1], "embargo token count test");
	printf("embargo token count: %d, expected: %d\n",testGame.embargoTokens[choice1],Game.embargoTokens[choice1]);

	printf("TEST 11: outpostPlayed does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.outpostPlayed == Game.outpostPlayed, "outpost played test");
	printf("outpost played result: %d, expected: %d\n", testGame.outpostPlayed, Game.outpostPlayed);

	printf("TEST 12: outpostTurn does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.outpostTurn == Game.outpostTurn, "outpost turn test");
	printf("outpost turn result: %d, expected: %d\n", testGame.outpostTurn, Game.outpostTurn);

	printf("TEST 13: whoseTurn does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.whoseTurn == Game.whoseTurn, "whose turn test");
	printf("whose turn result: %d, expected: %d\n", testGame.whoseTurn, Game.whoseTurn);

	printf("TEST 14: phase does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.phase == Game.phase, "phase test");
	printf("phase result: %d, expected: %d\n", testGame.phase, Game.phase);

	printf("TEST 15: numActions does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.numActions == Game.numActions, "num actions test");
	printf("num actions result: %d, expected: %d\n", testGame.numActions , Game.numActions);

	printf("TEST 16: coins does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.coins == Game.coins , "coins test");
	printf("coins result: %d, expected: %d\n", testGame.coins, Game.coins);

	printf("TEST 17: numBuys does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.numBuys == Game.numBuys, "num buys test");
	printf("num buys result: %d, expected: %d\n", testGame.numBuys, Game.numBuys);

	printf("TEST 18: discardCount does not change\n");
	//do game state copy for the test case
	memcpy(&testGame, &Game, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handPos, &bonus);
	Assert(testGame.discardCount[currentPlayer] == Game.discardCount[currentPlayer], "discard count test");
	printf("discard count: %d, expected: %d\n",testGame.discardCount[currentPlayer],Game.discardCount[currentPlayer]);	
	
	return 0;
}
