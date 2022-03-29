# Filename: makefile.mk
# Student Name: Greg Shalay (UoG: 1096689)
# File Description: Contains the compilation commands for tree.c.

CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g -DTREE

all: tree.o

all_tests: test1 ttest

clean:
	rm *.o
	rm test1
	rm ttest

tree.o: tree.h tree.c
	$(CC) $(CFLAGS) tree.c -o tree.o -c

test1: tree.o test1.o
	$(CC) $(CFLAGS) tree.o test1.o -o test1

ttest: tree.o ttest.o
	$(CC) $(CFLAGS) tree.o ttest.o -o ttest

test1.o: tree.h test1.c
	$(CC) $(CFLAGS) test1.c -o test1.o -c

ttest.o:
	$(CC) $(CFLAGS) ttest.c -o ttest.o -c