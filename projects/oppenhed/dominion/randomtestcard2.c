/*************************************************************
* Name: randomtestcard2.c
* Author: Diana Oppenheimer
* Date: 05/18/19
* Description: random testing of refactorVillage function
*************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TEST "refactorVillage"
#define NUM_TESTS 500

//Tester function
int assertTest(int eval, int aval) {
	if(eval != aval) {
		return -1;
	}
	return 1;
}

//Test Oracle
void check_refactorVillage(struct gameState *post, int handPos, int player, int *test1Fail, int *test2Fail, int *test3Fail, int *test4Fail) {
	
	//copy original game state post to pre for later comparison
	struct gameState *pre = malloc(sizeof(struct gameState));
	memcpy(pre, post, sizeof(struct gameState));

	//Run function
	int result;
	int bonus = 0;
	result = cardEffect(village, -1, -1, -1, post, handPos, &bonus);
	
	//confirm function is not broken
	assert(result == 0);
	
	//Test 1: hand count + 1 card, - 1 discard (village card)
	if(assertTest(pre->handCount[player], post->handCount[player]) == -1) {
		(*test1Fail)++;
	}

	//Test 2: discard count + 1 (village card)
	if(assertTest(pre->discardCount[player] + 1, post->discardCount[player]) == -1) {
		(*test2Fail)++;
	}

	//Test 3: deck count - 1 (added card)
	if(assertTest(pre->deckCount[player] - 1, post->deckCount[player]) == -1) {
		(*test3Fail)++;
	}

	//Test 4: numActions + 2
	if(assertTest(pre->numActions + 2, post->numActions) == -1) {
		(*test4Fail)++;
	}
	
	free(pre);
}

int main() {
	
	struct gameState *G;

	printf("------------Testing %s-------------\n", TEST);

	SelectStream(2);
	PutSeed(3);

	//Test count variables and messages
	int test1Fail = 0;
	int test2Fail = 0;
	int test3Fail = 0;
	int test4Fail = 0;

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
		check_refactorVillage(G, handPos, player, &test1Fail, &test2Fail, &test3Fail, &test4Fail);
		free(G);
	}

	//Report on testing results
	if(test1Fail > 0)
		printf("Testing if hand count is unchanged (+1 card, discard village card), failed %i times out of %i.\n", test1Fail, NUM_TESTS);
	else
		printf("Testing if hand count is unchanged (+1 card, discard village card), test passed.\n");
	if(test2Fail > 0)
		printf("Testing if discard count reflects + village, failed %i times out of %i.\n", test2Fail, NUM_TESTS);
	else
		printf("Testing if discard count reflects + village, test passed.\n");
	if(test3Fail > 0)
		printf("Testing if deck count reflects 1 card drawn, failed %i times out of %i.\n", test3Fail, NUM_TESTS);
	else
		printf("Testing if deck count reflects 1 card drawn, test passed.\n");
	if(test4Fail > 0)
		printf("Testing if numActions reflects +2 actions added, failed %i times out of %i.\n", test4Fail, NUM_TESTS);
	else
		printf("Testing if numActions reflects +2 actions added, test passed.\n");
	
	return 0;
	
	//free(G);
}
