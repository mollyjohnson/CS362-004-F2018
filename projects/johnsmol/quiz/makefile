#default: randomTest
#
#randomTest:
#	gcc -Wall -std=c99 -o randomTest testme.c -coverage -fpic -lm
#	valgrind ./randomTest
#
#clean:
#	rm randomTest testme.c.* testme.g*

CXX = gcc
CXXFLAGS = -std=c99
CXXFLAGS += -Wall
CXXFLAGS += -g
CXXFLAGS += -coverage
CXXFLAGS += -fpic
CXXFLAGS += -lm

LDFLAGS = -lboost_date_time
LDFLAGS += -fprofile-generate

OBJS = testme.o
SRCS = testme.c

testme: ${OBJS}
	${CXX} ${LDFLAGS} ${OBJS} -o testme

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.c)

clean:
	rm *.o testme
