#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function

	//rand num generator formula adapted from:
	//https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
	int minValue = 0;
	int maxValue = 9;
	int randIndex = (rand() % maxValue + minValue);
	char charOptions[] = "[({ ax})]";

    return charOptions[randIndex];
}

char *inputString()
{
    // TODO: rewrite this function

	int minValue = 0;
	int maxValue = 5;
	int randIndex;
	char charOptions[] = "reset";
	static char randString[6];

	//for (int i = 0; i < strlen(charOptions); i++)
	for ( int i = 0; i < 100; i++)
	{
			printf("i is: %d\n", i);
		randIndex = (rand() % maxValue + minValue);
		//randString[i] = charOptions[randIndex]; 	
		printf("rand number is: %d\n", randIndex);
	}

    return randString;
}

/*void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}
*/

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //testme();
	
	char *stringy = inputString();
	printf("%s\n", stringy);

    return 0;
}
