CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: testme

testme: testme.c

	echo "Random Test quiz testing of testme.c output:" >> testme.out
	gcc -o testme testme.c $(CFLAGS)
	./testme >> testme.out

clean:
	rm testme.out testme *.gcda *.gcno *.gcov
