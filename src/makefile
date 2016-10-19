CC= gcc
FLAGS= -Wall -Wextra -std=gnu99 -c
ENDFLAGS= -lpthread -lcrypt -lrt
OBJECTS= crack.o bruteforce.o

all: crack

crack: crack.o bruteforce.o
	gcc $(OBJECTS) -o crack

crack.o: crack.c
	$(CC) $(FLAGS) crack.c $(ENDFLAGS)

bruteforce.o: bruteforce.c bruteforce.h
	$(CC) $(FLAGS) bruteforce.c $(ENDFLAGS)

clean:
	rm *.o crack
