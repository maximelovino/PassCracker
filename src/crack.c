#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "bruteforce.h"

#ifndef STR_SIZE
#define STR_SIZE 128
#endif

char* createCharRange(char* pathOfRangeFile, int* rangeLength){
	FILE* file;
	file = fopen(pathOfRangeFile,"r");
	char line[STR_SIZE];
	if (file == NULL) {
		return NULL;
	}
	int lineCnt = 0;
	while (fgets(line,STR_SIZE,file) != NULL) {
		lineCnt++;
	}
	rewind(file);
	*rangeLength = lineCnt;
	char* range = malloc(sizeof(char)*lineCnt);
	lineCnt = 0;
	while (fgets(line,STR_SIZE,file) != NULL) {
		range[lineCnt] = line[0];
		lineCnt++;
	}
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
		int threadCount = atoi(argv[3]);
		int* winner = malloc(sizeof(int));
		*winner = -1;
		int* rangeLength = malloc(sizeof(int));

		char* range = createCharRange("range.txt",rangeLength);

		pthread_t threads[threadCount];

		for (int i = 0; i < threadCount; i++) {
			BFInfo* info = malloc(sizeof(BFInfo));
			info -> id = i;
			info -> m = threadCount;
			info -> rangeLength = *rangeLength;
			info -> salt = salt;
			info -> hash = hash;
			info -> range = range;
			info -> winner = winner;

			if (pthread_create(&(threads[i]),NULL,bruteforce,info)!=0) {
				fprintf(stderr, "There was a problem creating a thread\n");
				return EXIT_FAILURE;
			}
		}
		
		while (*winner == -1) {};

		char* result;

		pthread_join(threads[*winner],(void**)&result);

		for (int i = 0; i < threadCount; i++){
			pthread_cancel(threads[i]);
		}

		clock_gettime(CLOCK_MONOTONIC,&finish);
		double elapsedTime = finish.tv_sec - start.tv_sec;
		elapsedTime += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		printf("The password is %s\n",result);
		printf("The code has run during %f seconds\n", elapsedTime );
	}
	return 0;
}
