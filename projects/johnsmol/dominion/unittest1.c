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
	printf("unittest1 is working\n");	
	int a = 2;
	int b = 3;
	Assert(a == 2); //true
	Assert(a == b); //false
	Assert(b == b); //tue

	printf("reached the end");
	return 0;
}
