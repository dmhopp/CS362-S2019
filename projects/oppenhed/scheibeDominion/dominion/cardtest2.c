/*******************************************************************
* Name: cardtest2.c
* Author: Diana Oppenheimer
* Date: 05/05/19
* Description:
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rngs.h"
#include "dominion_helpers.h"
#include "dominion.h"

#define TEST "adventurer"

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
	
	//copy game state to test case
        memcpy(&Gtest, &G, sizeof(struct gameState));
	
	//Manipulate starting deck and hand
	Gtest.deck[0][0] = estate;
	Gtest.deck[0][1] = silver;
	Gtest.deck[0][2] = gold;
	Gtest.deck[0][3] = estate;
	Gtest.deck[0][4] = copper;
	Gtest.deck[0][5] = estate;
	Gtest.deckCount[0] = 6;
	Gtest.discardCount[0] = 0;

	int i;
	for(i = 0; i < MAX_HAND; i++) {
		Gtest.hand[0][i] = -1;
	}
	Gtest.hand[0][0] = estate;
	Gtest.hand[0][1] = estate;
	Gtest.hand[0][2] = estate;
	Gtest.hand[0][3] = estate;
	Gtest.hand[0][4] = adventurer;
	//Gtest.handCount[0] = 1;

        //Execute refactored adventurer function
	refactorAdventurer(&Gtest);

	//Testing
	assertTest(2, Gtest.deckCount[0], "Error: incorrect deck count.", &flag);
	assertTest(3, Gtest.discardCount[0], "Error: incorrect discard count.", &flag);
	assertTest(6, Gtest.handCount[0], "Error: incorrect hand count.", &flag);
	assertTest(copper, Gtest.hand[0][Gtest.handCount[0]-2], "Error: incorrect treasure type.", &flag);
	assertTest(gold, Gtest.hand[0][Gtest.handCount[0]-1], "Error: incorrect treasure type.", &flag);
	
	//Manipulate starting deck and hand
        G.deck[0][0] = estate;
        G.deck[0][1] = estate;
        G.deck[0][2] = estate;
        G.deck[0][3] = estate;
        G.deck[0][4] = estate;
        G.deck[0][5] = estate;
        G.deckCount[0] = 6;
        G.discardCount[0] = 0;

        for(i = 0; i < 5; i++) {
                G.hand[0][i] = estate;
        }
        G.hand[0][4] = adventurer;
        //G.handCount[0] = 1;

        //Execute refactored adventurer function
        refactorAdventurer(&G);

        //Testing
        assertTest(7, G.discardCount[0], "Error: incorrect discard count.", &flag);
        assertTest(4, G.handCount[0], "Error: incorrect hand count.", &flag);



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

