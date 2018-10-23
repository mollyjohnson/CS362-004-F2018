all: randomTest

randomTest:
	gcc -Wall -std=c99 -o randomTest testme.c -coverage -fpic -lm

clean:
	rm randomTest

cleanall:
	rm randomTest testme.c.* testme.g*
