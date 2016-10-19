CC= gcc
FLAGS= -Wall -Wextra -std=c99 -c
ENDFLAGS= -lpthread -lcrypt -lrt
OBJECTS= crack.o bruteforce.o

all: crack

crack: crack.o
	gcc $(OBJECTS) -o crack
	
crack.o: crack.c
	$(CC) $(FLAGS) crack.c

bruteforce.o: bruteforce.c bruteforce.h
	$(CC) $(FLAGS) bruteforce.c

clean:
	rm *.o crack
