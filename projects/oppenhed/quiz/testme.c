/***************************************************
* Name: testme.c
* Edited by: Diana Oppenheimer
* Description: random testing quiz
***************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define STR_LEN 6

//Name: inputChar
//Params: N/A
//Return: char
//Description: returns char in ascii range 32-127

char inputChar()
{
	char inputPool[] = "[({ ax})]";
	int randI = rand() % 9;
	char randC = inputPool[randI];
	return randC;
}

//Name: inputString
//Params: N/A
//Return: char*
//Description: returns pointer to random string of length STR_LEN

char *inputString()
{
	char randS[STR_LEN];
	char inputPool[] = "reset";
	int i;
	for(i = 0; i < STR_LEN - 1; i++) {
		int r = rand() % 5;
		randS[i] = inputPool[r];
	}
	randS[STR_LEN - 1] = '\0';
	char* product = randS;
	return product;
}

void testme()
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
    if (c == ' ' && state == 3) state = 4;
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


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
