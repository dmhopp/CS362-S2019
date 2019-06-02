/*******************************************************************************
* Author: Diana Oppenheimer
* Date: 04/27/18
* Name: unittest3.c
* Description: Implements a unit test of dominion.c function discardCard()
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>

#define TESTF "discardCard"

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
        printf("TESTING %s\n", TESTF);
	
	//copy game state to test case
        memcpy(&Gtest, &G, sizeof(struct gameState));

	//Test until boundary reached
	int handPos = 1;
	int handcount = G.handCount[0];
	while(handcount > 1) {
		discardCard(handcount, 0, &Gtest, -1);
		//printf("G = %i, Gtest = %i\n", G.handCount[0] - handPos, Gtest.handCount[0]);
		assertTest(G.handCount[0] - handPos, Gtest.handCount[0], "Error: incorrect hand count.", &flag);
		assertTest(G.playedCardCount + handPos, Gtest.playedCardCount, "Error: incorrect played card count.", &flag);
		handPos++;
		handcount--;
	}

	//Test boundary
	discardCard(1, 0, &Gtest, -1);
	assertTest(G.handCount[0] - 5, Gtest.handCount[0], "Error: incorrect hand count at boundary.", &flag);
	assertTest(G.playedCardCount + 5, Gtest.playedCardCount, "Error: incorrect played card count.", &flag);
	discardCard(0, 0, &Gtest, -1);
	assertTest(G.handCount[0] - 6, Gtest.handCount[0], "Error: incorrect hand count at boundary.", &flag);
	assertTest(G.playedCardCount + 6, Gtest.playedCardCount, "Error: incorrect played card count.", &flag);


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

