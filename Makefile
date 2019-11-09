.PHONY: str

CC=gcc 
FLAGS=-Wall -Wextra -pedantic -O0 -ggdb -std=gnu99
OUTPUT=bin/

# Output for headers will change in the future
vpath %.c src/
vpath %.h src/

str : string.c string.h
	$(CC) $(FLAGS) -o $(OUTPUT)$@ $(SOURCE)$<
