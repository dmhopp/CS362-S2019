/*******************************************************************
* Name: cardtest3.c
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

#define TEST "sea_hag"

void assertTest(int, int, char*, int*);


int main() {

        //Construct & init game
        int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int players = 3;
        int k[10] = {adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine};
        int seed = 10;
        struct gameState G;
        struct gameState Gtest;

        initializeGame(players, k, seed, &G);

        //Testing
        int flag = 0;
        printf("TESTING %s\n", TEST);

        //copy game state to test case
        memcpy(&Gtest, &G, sizeof(struct gameState));

        //Execute refactored sea_hag function
	cardEffect(sea_hag, choice1, choice2, choice3, &Gtest, handPos, &bonus);
        //refactorSeaHag(&Gtest);

        //Check for errors
	assertTest(whoseTurn(&Gtest), whoseTurn(&G), "Error: incorrect player turn.", &flag);
	
	assertTest(G.discardCount[0], Gtest.discardCount[0], "Error: current player incorrect discard count.", &flag);
	assertTest(G.discardCount[1] + 1, Gtest.discardCount[1], "Error: player 2 incorrect discard count.", &flag);
	assertTest(G.discardCount[2] + 1, Gtest.discardCount[2], "Error: player 3 incorrect discard count.", &flag);
	
	assertTest(G.deck[1][G.deckCount[1]-1], Gtest.discard[1][G.discardCount[1]], "Error: player 2 top discard card mismatch.", &flag);
	assertTest(G.deck[2][G.deckCount[2]-1], Gtest.discard[2][G.discardCount[2]], "Error: player 3 top discard card mismatch.", &flag);

	assertTest(G.deckCount[0], Gtest.deckCount[0], "Error: current player incorrect deck count.", &flag);
	assertTest(G.deckCount[1], Gtest.deckCount[1], "Error: player 2 incorrect deck count.", &flag);
	assertTest(G.deckCount[1], Gtest.deckCount[1], "Error: player 3 incorrect deck count.", &flag);

	assertTest(curse, Gtest.deck[1][Gtest.deckCount[1]-1], "Error: incorrect top deck card.", &flag);
	assertTest(curse, Gtest.deck[2][Gtest.deckCount[2]-1], "Error: incorrect top deck card.", &flag);

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
                //if(flag == 0) {
                //        aval = aval - 2;
                //}
                printf("FAIL:  %s (expected = %i, actual = %i)\n", msg, eval, aval);
                *flag = 1;
        }
}


