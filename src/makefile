CC= gcc
FLAGS= -Wall -Wextra -std=gnu99 -c
ENDFLAGS= -lpthread -lcrypt -lrt
OBJECTS= crack.o bruteforce.o

all: crack

crack: crack.o bruteforce.o
	$(CC) $(OBJECTS) -o crack $(ENDFLAGS)

crack.o: crack.c
	$(CC) $(FLAGS) crack.c
	
bruteforce.o: bruteforce.c bruteforce.h
	$(CC) $(FLAGS) bruteforce.c

clean:
	rm *.o crack
