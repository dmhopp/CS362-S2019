/*******************************************************************
* Name: cardtest4.c
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

#define TEST "village"

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

	int handpos = 0, c1 = 0, c2 = 0, c3 = 0, bonus = 0;
        //Execute cardEffect village function
        cardEffect(village, c1, c2, c3, &Gtest, handpos, &bonus);

        //Check for errors
	assertTest(G.handCount[0], Gtest.handCount[0], "Error: incorrect hand count.", &flag);

	assertTest(G.numActions + 2, Gtest.numActions, "Error: incorrect number of actions.", &flag);

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



