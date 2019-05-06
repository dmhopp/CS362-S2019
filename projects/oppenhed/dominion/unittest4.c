/*******************************************************************************
* Author: Diana Oppenheimer
* Date: 04/27/18
* Name: unittest4.c
* Description: Implements a unit test of dominion.c function isGameOver()
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>

#define TESTF "isGameOver"

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

	assertTest(isGameOver(&G), 0, "Error: game should not be over.", &flag);
	
	G.supplyCount[province] = 0;
	assertTest(isGameOver(&G), 1, "Error: gmae should be over.", &flag);

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
		*flag++;
	}
}
