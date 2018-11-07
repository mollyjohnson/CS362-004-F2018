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

#define TESTCARD "village"

//function declarations
void Assert(int expression, char *message);

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
	printf("random testing of village card\n");
	
	return 0;
}
