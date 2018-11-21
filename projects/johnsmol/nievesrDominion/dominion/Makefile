# Molly Johnson
# OSU CS 362 Fall 2018
# Assignment 3 makefile
# Due: 10/28/18

CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: all

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c
	echo "Results running for unit and card tests:" > tests.out
	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 -g -fpic -lm -coverage unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> tests.out
	
	echo "unittest2.c:" >> tests.out
	gcc -o unittest2 -g -fpic -lm -coverage unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> tests.out
	
	echo "unittest3.c:" >> tests.out
	gcc -o unittest3 -g -fpic -lm -coverage unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> tests.out
	
	echo "unittest4.c:" >> tests.out
	gcc -o unittest4 -g -fpic -lm -coverage unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> tests.out
	
	echo "cardtest1.c:" >> tests.out
	gcc -o cardtest1 -g -fpic -lm -coverage cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> tests.out
	
	echo "cardtest2.c:" >> tests.out
	gcc -o cardtest2 -g -fpic -lm -coverage cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> tests.out
	
	echo "cardtest3.c:" >> tests.out
	gcc -o cardtest3 -g -fpic -lm -coverage cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> tests.out
	
	echo "cardtest4.c:" >> tests.out
	gcc -o cardtest4 -g -fpic -lm -coverage cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> tests.out
	
	#run gcov on dominion.c with -f (function) flag and -b (branch) flag
	gcov dominion.c -f -b >> tests.out
	
randomtestresults: randomtestcard1.c randomtestcard2.c randomtestadventurer.c dominion.c
	echo "Results running for randomtestcard1.c (smithy)" > randomtestcard1.out
	echo "randomtestcard1.c (smithy):" >> randomtestcard1.out
	gcc -o randomtestcard1 -g -fpic -lm -coverage randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	#run gcov on dominion.c with -f (function) flag and -b (branch) flag
	gcov dominion.c -f -b >> randomtestcard1.out
	
	echo "Results running for randomtestcard2.c (village)" > randomtestcard2.out
	echo "randomtestcard2.c (village):" >> randomtestcard2.out
	gcc -o randomtestcard2 -g -fpic -lm -coverage randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	#run gcov on dominion.c with -f (function) flag and -b (branch) flag
	gcov dominion.c -f -b >> randomtestcard2.out
	
	echo "Results running for randomtestadventurer.c (adventurer)" > randomtestadventurer.out
	echo "randomtestadventurer.c (adventurer):" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g -fpic -lm -coverage randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	valgrind ./randomtestadventurer >> randomtestadventurer.out
	#run gcov on dominion.c with -f (function) flag and -b (branch) flag
	gcov dominion.c -f -b >> randomtestadventurer.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittestresults randomtestresults

clean:
	rm -f tests.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer *.gcda *.gcno *.gcov

cleanall:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f tests.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcda *.gcno *.gcov
	rm -f randomtestcart1.out randomtestcard2.out randomtestcard3.out
