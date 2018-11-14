/*
 * Molly Johnson
 * OSU CS 362 Fall 2018
 * Assignment 4
 * Due: 11/14/18
 * randomtestcard1.c
 * Some setup and general method for creating test game state, etc adapted from the
 * cardtest4.c steward example file provided in the OSU CS 362 Fall 2018 lectures as
 * well as my own work from my OSU CS 362 Fall 2018 Assignment 3.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD "village"

//one global variable
int testsPassed = 0;

//function declarations
void Assert(int expression, char *message);
int GetRandomNum(int minNum, int maxNum);

/*
 * random num function adapted from my own work created 10/25/18 
*/
int GetRandomNum(int minNum, int maxNum)
{
	int randNum = (rand() % (maxNum - minNum + 1) + minNum);

	return randNum;
}

/*
 * custom assert expression adapted from:
 * https://www.tutorialspoint.com/c_standard_library/assert_h.htm
*/
void Assert(int expression, char *message)
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
		testsPassed++;
	}
}

/*
 * This is the main function. Here the test variables will be declared/initialized,
 * randomization for the testing will occur, the printf() and custom Assert functions
 * will be called as needed to test the program's behavior, and (prior to calling those
 * function), a replica gameState and test gameState structure will be created for
 * the test suite.
*/
int main()
{
	printf("------------------------- Testing card: %s -------------------------\n", TESTCARD);
	//seed rand
	srand(time(NULL));
	int i;
	int testCount = 50;
	int tests = 0;
	for(i = 1; i <= testCount; i++)
	{ 
		//create variables
		int newCards = 0;
		int discardedCards = 1;
		int shuffledCards = 0;
		int numActions = 1;	
		//testsed with min num of players (2) and the dominion.h max of 4.
		int numPlayers = GetRandomNum(2, 4);

		//randomize other player besides current player to be any of the other players
		int otherPlayer;

		//randomize choices and bonuses
		int choice1 = GetRandomNum(0, 100);
		int choice2 = GetRandomNum(0, 100); 
		int choice3 = GetRandomNum(0, 100); 
		int bonus = GetRandomNum(0, 100); 

		//max hand of 500 taken from the code
		int maxHand = 500; 
		int handPos = GetRandomNum(0,maxHand);;
		
		//seed used to get game randomness
		int seed = GetRandomNum(1, 2000);
		
		//create a game state and a test game state
		struct gameState Game, testGame;
		//10 "action" cards are allowed per game (tho these can differ per game). are 27 options total in this version
		//of dominion, but you're only allowed 10 per game so only 10 will be tested in this test suite
		int kingdomCards[10] = { smithy, adventurer, village, baron, minion, great_hall, council_room, steward, gardens, mine };

		//initialize the game with the given num of players and variables
		initializeGame(numPlayers, kingdomCards, seed, &Game);
		
		printf("------------------------- Random test: %d  -------------------------\n", i);	
		printf("for each random test, will test with all players as the current player in sequential order (indicated by current player number from positions 0 to \n");
		printf("numPlayers - 1), and will select  another player at random to be the other player and check for gamestate changes to other players.\n");

		int k;
		for(k = 0; k < numPlayers; k++)
		{
			//randomize another player who's not the current player
			do{
				otherPlayer = GetRandomNum(0, numPlayers - 1); 
			}while(otherPlayer == k);
			
			testGame.handCount[k] = GetRandomNum(0, (MAX_HAND));
			testGame.deckCount[k] = ((GetRandomNum(0, (MAX_DECK))) - testGame.handCount[k]);
			testGame.whoseTurn = k;
			Game.handCount[k] = testGame.handCount[k]; 
			Game.deckCount[k] = testGame.deckCount[k];
			Game.whoseTurn = k;

			printf("\nRandom test %d , iteration %d,  current player %d, random other player %d randomized variable values:\n", i, k, k, otherPlayer);

			printf("num players: %d\n", numPlayers);
			printf("current player: %d\n", k);
			printf("random other player: %d\n", otherPlayer);
			printf("choice 1: %d\n", choice1);
			printf("choice 2: %d\n", choice2);
			printf("choice 3: %d\n", choice3);
			printf("bonus: %d\n", bonus);
			printf("hand position: %d\n", handPos);
			printf("seed for game randomization: %d\n\n", seed);
			printf("testGame.handCount[k] is: %d\n",testGame.handCount[k]);
			printf("testGame.deckCount[k] is: %d\n",testGame.deckCount[k]);
			printf("Game.handCount[k] is: %d\n",Game.handCount[k]);
			printf("Game.deckCount[k] is: %d\n\n",Game.deckCount[k]);

			printf("TEST 1: current player receives 1 card \n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			newCards = 1;
			Assert(testGame.handCount[k] == (Game.handCount[k] + newCards -discardedCards), "hand count test");
			tests++;
			printf("hand count: %d, expected: %d\n", testGame.handCount[k],Game.handCount[k] + newCards -discardedCards);
			//reset any changed variables
			newCards = 0;
			
			printf("TEST 2: 1 card come from the current player's deck\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.deckCount[k] == (Game.deckCount[k] - discardedCards), "deck count test");
			tests++;
			printf("deck count: %d, expected: %d\n", testGame.deckCount[k], Game.deckCount[k] - discardedCards + shuffledCards);
			//reset any changed variables

			printf("TEST 3: discard pile stays the same (since card is played not trashed)\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.discardCount[k] == (Game.discardCount[k]), "discard pile test");
			tests++;
			printf("discard count: %d, expected: %d\n", testGame.discardCount[k], Game.discardCount[k]);

			printf("TEST 4: no state change for things specific to other players (hand count, deck count, discard count\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.handCount[otherPlayer] == (Game.handCount[otherPlayer]), "other player hand count test");
			tests++;
			printf("other player hand count: %d, expected: %d\n", testGame.handCount[otherPlayer],Game.handCount[otherPlayer]);
			Assert(testGame.deckCount[otherPlayer] == (Game.deckCount[otherPlayer]), "other player deck count test");
			tests++;
			printf("other player's deck count: %d, expected: %d\n", testGame.deckCount[otherPlayer], Game.deckCount[otherPlayer]);
			Assert(testGame.discardCount[otherPlayer] == (Game.discardCount[otherPlayer]), "other player discard pile test");
			tests++;
			printf("other player discard count: %d, expected: %d\n", testGame.discardCount[otherPlayer], Game.discardCount[otherPlayer]);

			printf("TEST 5: no state change to victory card piles\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			//kingdomcards in this game
			//int kingdomCards[10] = { village, adventurer, village, baron, minion, great_hall, council_room, steward, gardens, mine };
			Assert(testGame.supplyCount[smithy] == Game.supplyCount[smithy], "kingdom card smithy test");
			tests++;
			printf("kingdom card smithy count: %d, expected: %d\n",testGame.supplyCount[smithy],Game.supplyCount[village]); 
			Assert(testGame.supplyCount[adventurer] == Game.supplyCount[adventurer], "kingdom card adventurer test");
			tests++;
			printf("kingdom card adventurer count: %d, expected: %d\n",testGame.supplyCount[adventurer],Game.supplyCount[adventurer]); 
			Assert(testGame.supplyCount[village] == Game.supplyCount[village], "kingdom card village test");
			tests++;
			printf("kingdom card village count: %d, expected: %d\n",testGame.supplyCount[village],Game.supplyCount[village]); 
			Assert(testGame.supplyCount[baron] == Game.supplyCount[baron], "kingdom card baron test");
			tests++;
			printf("kingdom card baron count: %d, expected: %d\n",testGame.supplyCount[baron],Game.supplyCount[baron]); 
			Assert(testGame.supplyCount[minion] == Game.supplyCount[minion], "kingdom card minion test");
			tests++;
			printf("kingdom card minion count: %d, expected: %d\n",testGame.supplyCount[minion],Game.supplyCount[minion]); 
			Assert(testGame.supplyCount[great_hall] == Game.supplyCount[great_hall], "kingdom card great_hall test");
			tests++;
			printf("kingdom card great_hall count: %d, expected: %d\n",testGame.supplyCount[great_hall],Game.supplyCount[great_hall]); 
			Assert(testGame.supplyCount[council_room] == Game.supplyCount[council_room], "kingdom card council_room test");
			tests++;
			printf("kingdom card council_room count: %d, expected: %d\n",testGame.supplyCount[council_room],Game.supplyCount[council_room]); 
			Assert(testGame.supplyCount[steward] == Game.supplyCount[steward], "kingdom card steward test");
			tests++;
			printf("kingdom card steward count: %d, expected: %d\n",testGame.supplyCount[steward],Game.supplyCount[steward]); 
			Assert(testGame.supplyCount[gardens] == Game.supplyCount[gardens], "kingdom card gardens test");
			tests++;
			printf("kingdom card gardens count: %d, expected: %d\n",testGame.supplyCount[gardens],Game.supplyCount[gardens]); 
			Assert(testGame.supplyCount[mine] == Game.supplyCount[mine], "kingdom card mine test");
			tests++;
			printf("kingdom card mine count: %d, expected: %d\n",testGame.supplyCount[mine],Game.supplyCount[mine]); 
			
			printf("TEST 6: no state change to kingdom card piles\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.supplyCount[estate] == Game.supplyCount[estate], "victory card estate test");
			tests++;
			printf("victory card estate count: %d, expected: %d\n",testGame.supplyCount[estate],Game.supplyCount[estate]); 
			Assert(testGame.supplyCount[duchy] == Game.supplyCount[duchy], "victory card duchy test");
			tests++;
			printf("victory card duchy count: %d, expected: %d\n",testGame.supplyCount[duchy],Game.supplyCount[duchy]); 
			Assert(testGame.supplyCount[province] == Game.supplyCount[province], "victory card province test");
			tests++;
			printf("victory card province count: %d, expected: %d\n",testGame.supplyCount[province],Game.supplyCount[province]); 

			printf("TEST 7: played card pile increases by 1 (since original card is played not trashed)\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.playedCardCount == (Game.playedCardCount + discardedCards), "played card pile test");
			tests++;
			printf("played card count count: %d, expected: %d\n", testGame.playedCardCount, Game.playedCardCount + discardedCards);

			printf("TEST 8: numPlayers does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.numPlayers == Game.numPlayers, "other player hand count test");
			tests++;
			printf("num players: %d, expected: %d\n", testGame.numPlayers, Game.numPlayers);

			printf("TEST 9: embargoTokens does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.embargoTokens[choice1] == Game.embargoTokens[choice1], "embargo token count test");
			tests++;
			printf("embargo token count: %d, expected: %d\n",testGame.embargoTokens[choice1],Game.embargoTokens[choice1]);

			printf("TEST 10: outpostPlayed does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.outpostPlayed == Game.outpostPlayed, "outpost played test");
			tests++;
			printf("outpost played result: %d, expected: %d\n", testGame.outpostPlayed, Game.outpostPlayed);

			printf("TEST 11: outpostTurn does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.outpostTurn == Game.outpostTurn, "outpost turn test");
			tests++;
			printf("outpost turn result: %d, expected: %d\n", testGame.outpostTurn, Game.outpostTurn);

			printf("TEST 12: whoseTurn does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.whoseTurn == Game.whoseTurn, "whose turn test");
			tests++;
			printf("whose turn result: %d, expected: %d\n", testGame.whoseTurn, Game.whoseTurn);

			printf("TEST 13: phase does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.phase == Game.phase, "phase test");
			tests++;
			printf("phase result: %d, expected: %d\n", testGame.phase, Game.phase);

			numActions = 2;
			printf("TEST 14: numActions for current player increases by 2\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.numActions == Game.numActions, "num actions test to increase by 2");
			tests++;
			printf("num actions result: %d, expected: %d\n", testGame.numActions , Game.numActions + numActions);
			numActions = 1;

			printf("TEST 15: coins does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.coins == Game.coins , "coins test");
			tests++;
			printf("coins result: %d, expected: %d\n", testGame.coins, Game.coins);

			printf("TEST 16: numBuys does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.numBuys == Game.numBuys, "num buys test");
			tests++;
			printf("num buys result: %d, expected: %d\n", testGame.numBuys, Game.numBuys);

			printf("TEST 17: discardCount does not change\n");
			//do game state copy for the test case
			memcpy(&testGame, &Game, sizeof(struct gameState));
			cardEffect(village, choice1, choice2, choice3, &testGame, handPos, &bonus);
			Assert(testGame.discardCount[k] == Game.discardCount[k], "discard count test");
			tests++;
			printf("discard count: %d, expected: %d\n",testGame.discardCount[k],Game.discardCount[k]);
		}
	}

	printf("\ntotal num of tests run: %d\ntotal num of tests passed: %d\n\n", tests, testsPassed);

	return 0;
}
