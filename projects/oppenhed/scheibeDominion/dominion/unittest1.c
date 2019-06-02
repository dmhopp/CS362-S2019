/*******************************************************************************
* Author: Diana Oppenheimer
* Date: 04/27/18
* Name: unittest1.c
* Description: Implements a unit test of dominion.c function whoseTurn(struct)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "rngs.h"
#include "dominion.h"

#define TESTF "whoseTurn()"

void assertTest(int, int, char*, int*); 

int main() {
	
	//Construct & init game
	int players = 2;
	int k[10] = {adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine};
	int seed = 10;
	struct gameState G;
	
	initializeGame(players, k, seed, &G);

	//Testing
	int flag = 0;
	printf("TESTING %s\n", TESTF);
	
	//Confirm that initializeGame sets whoseTurn to 0 (player 1)
	assertTest(0, whoseTurn(&G), "Error: game does not initialize player 1 with starting turn.", &flag);
	//Positive test for all possible player values
	int i;
	for(i = 0; i < MAX_PLAYERS; i++) {
		G.whoseTurn = i;
		assertTest(i, whoseTurn(&G), "Error: incorrect turn assignment.", &flag);
	}
	
	//Conclusion: pass/fail
	if(flag == 0){
		printf("TESTING PASSED\n");
	}
	else {
		printf("TESTING FAILED\n");
	}

	return 0;
}

void assertTest(int eval, int aval, char* msg, int* flag) {
	if(eval != aval) {
		printf("FAIL:  %s (expected = %i, actual = %i)\n", msg, eval, aval);
		*flag = 1;
	}
}
