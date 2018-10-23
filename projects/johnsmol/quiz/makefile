default: randomTest

randomTest:
	gcc -Wall -std=c99 -o randomTest testme.c -coverage -fpic -lm
	valgrind ./randomTest

clean:
	rm randomTest testme.c.* testme.g*
