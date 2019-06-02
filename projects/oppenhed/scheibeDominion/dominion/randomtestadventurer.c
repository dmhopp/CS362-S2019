/*************************************************************
* Name: randomtestadventurer.c
* Author: Diana Oppenheimer
* Date: 05/18/19
* Description: 
*************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TEST "refactorAdventurer"
#define NUM_TESTS 500

//Tester function
int assertTest(int eval, int aval) {
	if(eval != aval) {
		return -1;
	}
	return 1;
}

//Test Oracle
void check_refactorAdventurer(struct gameState *post, int handPos, int player, int *test1Fail, int *test2Fail, int *test3Fail, int *test4Fail, int *test5Fail) {
	
	//copy original game state post to pre for later comparison
	struct gameState *pre = malloc(sizeof(struct gameState));
	memcpy(pre, post, sizeof(struct gameState));

	//Run function
	int result;
	int bonus = 0;
	result = cardEffect(adventurer, -1, -1, -1, post, handPos, &bonus);
	
	//confirm function is not broken
	assert(result == 0);
	
	//Test: if 1+ treasure card(s) in pre deck/discard...
	int i;
	int card1, card2;
	
	int preHT = 0;
	for(i = 0; i < pre->handCount[player]; i++) {
		if(pre->hand[player][i] >= 4 && pre->hand[player][i] <= 6) {
			preHT++;
		}
	}
	
	int postHT = 0;
	for(i = 0; i < post->handCount[player]; i++) {
		if(post->hand[player][i] >= 4 && post->hand[player][i] <= 6) {
			postHT++;
		}
	}
	
	int preDT = 0;
	if(pre->deckCount[player] > 0) {
	for(i = pre->deckCount[player] - 1; i >= 0; i--) {
		if(pre->deck[player][i] >= 4 && pre->deck[player][i] <= 6) {
			preDT++;
			if(preDT == 1) {
				card1 = pre->deck[player][i];
			}
			else if(preDT == 2) {
				card2 = pre->deck[player][i];
			}
		}
	}
	}	
	
	//int preDiscardT = 0;
	if(pre->discardCount[player] > 0) {
	for(i = pre->discardCount[player] - 1; i >= 0; i--) {
		if(pre->discard[player][i] >= 4 && pre->discard[player][i] <= 6) {
			//preDiscardT++;
			preDT++;
			if(preDT == 1) {
				card1 = pre->discard[player][i];
			}
			else if(preDT == 2) {
				card2 = pre->discard[player][i];
			}
		}
	}
	}
	
	int addedT = preDT;
	if(preDT > 2) {
		addedT = 2;
	}
	
	//...treasure count in hand + num treasure cards
	if(assertTest(addedT + preHT, postHT) == -1) {
		(*test1Fail)++;
	}
	
	//...hand count + num treasure cards - adventurer card
	if(assertTest(pre->handCount[player] + addedT - 1, post->handCount[player]) == -1) {
		(*test2Fail)++; 	
	}

	//...last card(s) in hand match last card(s) in deck 
	if(addedT == 2) {
		if(assertTest(card1, post->hand[player][post->handCount[player]-2]) == -1) {
			(*test3Fail)++;
		}
		if(assertTest(card2, post->hand[player][post->handCount[player]-1]) == -1) {
			(*test4Fail)++;
		}
	}
	else if(addedT == 1) {
		if(assertTest(card1, post->hand[player][post->handCount[player]-1]) == -1) {
			(*test3Fail)++;
		}
	}
	
	//...discard + deck count - num treasure cards + adventurer card
	if(assertTest(pre->discardCount[player]+pre->deckCount[player]-addedT+1, post->discardCount[player]+post->deckCount[player]) == -1) {
		(*test5Fail)++;
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
	int test4Fail = 0;
	int test5Fail = 0;

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
		check_refactorAdventurer(G, handPos, player, &test1Fail, &test2Fail, &test3Fail, &test4Fail, &test5Fail);
		free(G);
	}

	//Report on testing results
	if(test1Fail > 0)
		printf("Testing if 0-2 treasure added to hand, failed %i times out of %i.\n", test1Fail, NUM_TESTS);
	else
		printf("Testing if 0-2 treasure added to hand, test passed.\n");
	if(test2Fail > 0)
		printf("Testing if hand count reflects + treasure, - adventurer, failed %i times out of %i.\n", test2Fail, NUM_TESTS);
	else
		printf("Testing if hand count reflects + treasure, - adventurer, test passed.\n");
	if(test3Fail > 0)
		printf("Testing if first added card in hand matches first treasure card drawn, failed %i times out of %i.\n", test3Fail, NUM_TESTS);
	else
		printf("Testing if first added card in hand matches first treasure card drawn, test passed.\n");
	if(test4Fail > 0)
		printf("Testing if second added card in hand matches second treasure card drawn, failed %i times out of %i.\n", test4Fail, NUM_TESTS);
	else
		printf("Testing if second added card in hand matches second treasure card drawn, test passed.\n");
	if(test5Fail > 0)
		printf("Testing if discard + deck count reflects - treasure + adventurer, failed %i times out of %i.\n", test5Fail, NUM_TESTS);
	else
		printf("Testing if discard + deck count reflects - treasure + adventurer, test passed.\n");
	
	return 0;
	
	//free(G);
}
