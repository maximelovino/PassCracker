/**
 * Crack source file (main file, entry point of program)
 * @file 	crack.c
 * @project	PassCracker
 * @author	Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date	November 3, 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sched.h>
#include "bruteforce.h"

#ifndef STR_SIZE
#define STR_SIZE 128
#endif

/**
 * Creates the range of characters our password can use
 * @param  pathOfRangeFile	The path of the file containing the alphabet, on a single line
 * @param  rangeLength		A pointer to an int where we will store the length of the alphabet
 * @return					The alphabet
 */
char* createCharRange(char* pathOfRangeFile, int* rangeLength){
	FILE* file;
	file = fopen(pathOfRangeFile,"r");
	char line[STR_SIZE];
	char* range;
	if (fgets(line,STR_SIZE,file) != NULL) {
		*rangeLength = strlen(line)-1;
		range = malloc(sizeof(char)*(*rangeLength));
		for (int i = 0; i < *rangeLength; i++) {
			range[i] = line[i];
		}
	}

	fclose(file);
	return range;
}



int main(int argc, char const *argv[]) {
	if (argc!=4) {
		printf("Your arguments are invalid\n");
	}else{
		struct timespec start,finish;
		clock_gettime(CLOCK_MONOTONIC,&start);
		char hash[strlen(argv[1])];
		strcpy(hash,argv[1]);
		char salt[strlen(argv[2])];
		strcpy(salt,argv[2]);
		int match = 1;
		for (size_t i = 0; i < strlen(salt); i++) {
			if (hash[i]!=salt[i]) {
				match = 0;
			}
		}

		if (!match) {
			printf("The salt is not valid for this hash\n");
			return 0;
		}

		int threadCount = atoi(argv[3]);
		int winner = -1;
		int rangeLength = 0;

		char* range = createCharRange("range.txt", &rangeLength);

		pthread_t threads[threadCount];

		for (int i = 0; i < threadCount; i++) {
			BFInfo* info = malloc(sizeof(BFInfo));
			if(info == NULL) {
				return EXIT_FAILURE;
			}
			info->id = i;
			info->m = threadCount;
			info->rangeLength = rangeLength;
			info->salt = salt;
			info->hash = hash;
			info->range = range;
			info->winner = &winner;
			if (pthread_create(&(threads[i]),NULL,bruteforce,info)!=0) {
				fprintf(stderr, "There was a problem creating a thread\n");
				return EXIT_FAILURE;
			}
		}

		char* result;
		int resultAcquired = 0;
		for (int i = 0; i < threadCount; i++){
			if(i == winner || !resultAcquired) {
				pthread_join(threads[i],(void**)&result);
				resultAcquired = 1;
			} else {
				pthread_join(threads[i], NULL);
			}
		}

		clock_gettime(CLOCK_MONOTONIC,&finish);
		double elapsedTime = finish.tv_sec - start.tv_sec;
		elapsedTime += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		printf("The password is %s\n", result);
		printf("It took %f seconds to find the result\n", elapsedTime);
		free(range);
		free(result);
	}
	return 0;
}
