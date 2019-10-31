.PHONY=str

CC=gcc 
FLAGS=-Wall -Wextra -pedantic -O0 -g -std=gnu99
OUTPUT=bin/
SOURCE=src/

str : src/string.c src/string.h
	$(CC) $(FLAGS) -o $(OUTPUT)str $(SOURCE)string.c
