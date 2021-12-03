CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -fsanitize=undefined -fsanitize=address -g3
LDLIBS= -lm

crossword : crossword.c cwddriver.c crossword.h
	$(CC) crossword.c cwddriver.c -o crossword $(CFLAGS) $(LDLIBS)
