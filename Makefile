.PHONY: clean

CC=gcc 
FLAGS=-Wall -Wextra -pedantic -ggdb -std=gnu99
OUTPUT=bin/

# Output for headers will change in the future
vpath list.% src/list/

list.o : list.c list.h
	$(CC) $(FLAGS) -o $(OUTPUT)$@ $^

clean : 
	rm $(OUTPUT)string.o $(OUTPUT)test.o $(OUTPUT)test
