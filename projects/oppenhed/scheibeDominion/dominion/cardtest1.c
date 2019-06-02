/*******************************************************************
* Name: cardtest1.c
* Author: Diana Oppenheimer
* Date: 05/04/19
* Description:
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rngs.h"
#include "dominion_helpers.h"
#include "dominion.h"

#define TEST "smithy"

void assertTest(int, int, char*, int*);


int main() {
	
	//Construct & init game
        int players = 2;
        int k[10] = {adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine};
        int seed = 10;
        struct gameState G;
	struct gameState Gtest;

        initializeGame(players, k, seed, &G);

	//Testing
	int flag = 0;
	printf("TESTING %s\n", TEST);
	int handPos = 0;

	//copy game state to test case
	memcpy(&Gtest, &G, sizeof(struct gameState));
	
	//Execute refactored smithy function
	refactorSmithy(&Gtest, handPos);
	
	//Check for errors
	assertTest(G.handCount[0] + 2, Gtest.handCount[0], "Error: incorrect hand count.", &flag);
	int i;
	for(i = 0; i < 3; i++) {
		if(Gtest.hand[0][i] < 0 || Gtest.hand[0][i] > 26) {
			printf("FAIL: Error: drawn card does not exist.");
			flag = 1;
		}
	} 
	assertTest(G.deckCount[0] - 3, Gtest.deckCount[0], "Error: deck count mismatch.", &flag);

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
		if(flag == 0) {
			aval = aval - 2;
		}
                printf("FAIL:  %s (expected = %i, actual = %i)\n", msg, eval, aval);
                *flag = 1;
        }
}
