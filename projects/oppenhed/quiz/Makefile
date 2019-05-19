CFLAGS = -Wall -fpic -coverage -lm -std=c99

testme.o:
	gcc -o testme testme.c $(CFLAGS)

runtests: testme.o
	echo "Random Test quiz testing of testme.c output:" >> testme.out
	./testme >> testme.out
	gcov testme.c >> testme.out
	cat testme.c.gcov >> testme.out

clean:
	rm -f *.o *.out testme *.gcno *.gcov
