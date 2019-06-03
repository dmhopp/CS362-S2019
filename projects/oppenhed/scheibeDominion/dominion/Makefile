CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o 
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	
	echo "Results for unittest1: " >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 whoseTurn >> unittestresults.out
	
	echo "Results for unittest2: " >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 fullDeckCount >> unittestresults.out
	echo >> unittestresults.out
	
	echo "Results for unittest3: " >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 discardCard >> unittestresults.out
	echo >> unittestresults.out
	
	echo "Results for unittest4: " >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 isGameOver >> unittestresults.out
	echo >> unittestresults.out
	
	echo "Results for cardtest1: " >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 smithyEffect >> unittestresults.out
	echo >> unittestresults.out
	
	echo "Results for cardtest2: " >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 adventurerEffect >> unittestresults.out
	echo >> unittestresults.out
	
	echo "Results for cardtest3: " >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 cardEffect >> unittestresults.out
	echo >> unittestresults.out
	
	echo "Results for cardtest4: " >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c | grep -A4 villageEffect >> unittestresults.out
	echo >> unittestresults.out

randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2

	echo "Results for randomtestadventurer: " >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov -b -f dominion.c | grep -A4 adventurerEffect >> randomtestresults.out
	echo >> randomtestresults.out

	echo "Results for randomtestcard1: " >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	gcov -b -f dominion.c | grep -A4 smithyEffect >> randomtestresults.out
	echo >> randomtestresults.out

	echo "Results for randomtestcard2: " >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov -b -f dominion.c | grep -A4 villageEffect >> randomtestresults.out
	echo >> randomtestresults.out

	echo "dominion.c.gcov: " >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	echo >> randomtestresults.out

test: unittestresults randomtestresults

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe randomtestadventurer randomtestcard1 randomtestcard2 randomtestresults.out unittestresults.out cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	rm -fr *.dSYM
