/*******************************************************************************
* Author: Diana Oppenheimer
* Date: 04/27/18
* Name: unittest1.c
* Description: Implements a unit test of dominion.c function fullDeckCount
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rngs.h"
#include "dominion.h"

#define TESTF "fullDeckCount"

void assertTest(int, int, char*, int*);

int main() {

        //Construct & init game
        int players = 2;
        int k[10] = {adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine};
        int seed = 10;
        struct gameState G;

        initializeGame(players, k, seed, &G);

        //Testing
	int deckCount;
	int handCount;
	int discardCount;
	int cardCount;
        int flag = 0;
        printf("TESTING %s\n", TESTF);

        //Confirm initializeGame starts player 1  with 10 cards
	// 0 as card value bc 0 value used in scoring function
	assertTest(10, fullDeckCount(0, 0, &G), "Error: initial card count wrong.", &flag);

	//Test if fullDeck matches deck+hand+discard
	deckCount = G.deckCount[0];
	//printf("deck = %i", deckCount);
	handCount = G.handCount[0];
	//printf("hand = %i", handCount);
	discardCount = G.discardCount[0];
	//printf("discard = %i", discardCount);
	cardCount = deckCount+handCount+discardCount;
	assertTest(cardCount, fullDeckCount(0, 0, &G), "Error: card count mismatched.", &flag);
	
	//Test if fullDeck count of hand of pure gold is accurate
	int i;
	int card = gold;
	for(i = 0; i < 5; i++) {
		G.hand[0][i] = card;
	}
	G.handCount[0] = 5;
	for(i = 0; i < 5; i++) {
		G.deck[0][i] = card;
	}
	G.deckCount[0] = 5;
	assertTest(10, fullDeckCount(0, card, &G), "Error: incorrect number of gold counted.", &flag);

	//Test for copper when deck is pure gold
	int card2 = copper;
	assertTest(0, fullDeckCount(0, card2, &G), "Error: nonexistent card counted.", &flag);
	
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

