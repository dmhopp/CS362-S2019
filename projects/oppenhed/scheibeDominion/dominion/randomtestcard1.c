/*************************************************************
* Name: randomtestcard1.c
* Author: Diana Oppenheimer
* Date: 05/18/19
* Description: random testing of Smithy card function
*************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TEST "refactorSmithy"
#define NUM_TESTS 500

//Tester function
int assertTest(int eval, int aval) {
	if(eval != aval) {
		return -1;
	}
	return 1;
}

//Test Oracle
void check_refactorSmithy(struct gameState *post, int handPos, int player, int *test1Fail, int *test2Fail, int *test3Fail) {
	
	//copy original game state post to pre for later comparison
	struct gameState *pre = malloc(sizeof(struct gameState));
	memcpy(pre, post, sizeof(struct gameState));

	//Run function
	int result;
	int bonus = 0;
	result = cardEffect(smithy, -1, -1, -1, post, handPos, &bonus);
	
	//confirm function is not broken
	assert(result == 0);

	//Test player adds 3 cards to hand and discards Smithy card
	if(assertTest(pre->handCount[player] + 3 - 1, post->handCount[player]) == -1) {
		(*test1Fail)++;
	}
	
	//Test deck has decremented by 3
	if(assertTest(pre->deckCount[player] - 3, post->deckCount[player]) == -1) {
		(*test2Fail)++;
	}
	
	//Test player adds 1 card to discard pile (smithy card)
	if(assertTest(pre->discardCount[player] + 1, post->discardCount[player]) == -1) {
		(*test3Fail)++;
	}
	
	free(pre);
}

int main() {
	
	//int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	struct gameState *G;

	printf("------------Testing %s-------------\n", TEST);

	SelectStream(2);
	PutSeed(3);

	//Test count variables and messages
	int test1Fail = 0;
	int test2Fail = 0;
	int test3Fail = 0;

	//randomize game state within preconditions
	int n;
	int i;
	int numPlayers;
	int player;
	int handPos;
	for(n = 0; n < NUM_TESTS; n++) {
		G = malloc(sizeof(struct gameState));
		for(i = 0; i < sizeof(struct gameState); i++) {
			//assign each game state byte to random val
			((char*)G)[i] = floor(Random() * 256);
		}
		//refine variables to within preconditions
		//randomize players
		numPlayers = floor(Random() * MAX_PLAYERS);
		player = floor(Random() * numPlayers);
		G->whoseTurn = player;
		//randomize discard
		G->discardCount[player] = floor(Random() * MAX_DECK);
		G->playedCardCount = 0;
		//randomize hand
		G->handCount[player] = floor(Random() * MAX_HAND);
		handPos = floor(Random() * G->handCount[player]);
		int c;
		for(c = 0; c < G->handCount[player]; c++) {
			G->hand[player][c] = floor(Random() * 26);
		}
		//randomize deck
		G->deckCount[player] = floor(Random() * MAX_DECK);
		for(c = 0; c < G->deckCount[player]; c++) {
			G->deck[player][c] = floor(Random() * 26);
		}
		//check_refactorSmithy(G, handPos, player, &test1Fail, &test2Fail, &test3Fail);
		free(G);
	}

	//Report on testing results
	if(test1Fail > 0)
		printf("Testing if 3 cards added to hand, 1 card discarded, failed %i times out of %i.\n", test1Fail, NUM_TESTS);
	else
		printf("Testing if 3 cards added to hand, 1 card removed, test passed.\n");
	if(test2Fail > 0)
		printf("Testing if 3 cards taken from deck, failed %i times out of %i.\n", test2Fail, NUM_TESTS);
	else
		printf("Testing if 3 cards taken from deck, test passed.\n");
	if(test3Fail > 0)
		printf("Testing if 1 card added to discard, failed %i times out of %i.\n", test3Fail, NUM_TESTS);
	else
		printf("Testing if 1 card added to discard, test passed.\n");
	
	return 0;
	
	//free(G);
}
