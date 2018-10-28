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
void Assert(int expression);

/*

custom assert expression adapted from:
https://www.tutorialspoint.com/c_standard_library/assert_h.htm
*/
void Assert(int expression)
{	
	if(expression == 0)
	{
		printf("TEST FAILED\n");
	}
	else
	{
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}
}

/*

*/
int main()
{
	

	return 0;
}
