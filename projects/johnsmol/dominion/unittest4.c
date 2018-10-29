/*
Molly Johnson
OSU CS 362 Fall 2018
Assignment 3
Due: 10/28/18
unittest4.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
This is the main function. Here the test variables will be declared/initialized,
the printf() and custom Assert functions will be called as needed to test the
program's behavior, and (prior to calling those functions), a replica gameState
and test gameState structure will be created for the test suite.
*/
int main()
{
	printf("unittest4 is working\n");	

	return 0;
}
