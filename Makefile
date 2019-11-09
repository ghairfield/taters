.PHONY: clean

CC=gcc 
FLAGS=-Wall -Wextra -pedantic -O0 -ggdb -std=gnu99
OUTPUT=bin/

# Output for headers will change in the future
vpath %.c src/
vpath %.c test/
vpath %.h src/
vpath %.o bin/


test : test.o string.o 
	$(CC) $(FLAGS) -o $(OUTPUT)test $(OUTPUT)test.o $(OUTPUT)string.o

test.o : test.c string.h
	$(CC) $(FLAGS) -c -o $(OUTPUT)$@ $<

string.o : string.c string.h
	$(CC) $(FLAGS) -c -o $(OUTPUT)$@ $<

clean : 
	rm $(OUTPUT)string.o $(OUTPUT)test.o $(OUTPUT)test
