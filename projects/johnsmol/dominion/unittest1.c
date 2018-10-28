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
	/*int newCards = 0;
	int discarded = 1;
	int extraCoind = 0;
	int shuffledCards = 0;
	int numPlayers = 2;
	struct gameState Game, testGame;
	int cards[10] = { 
*/
	return 0;
}
