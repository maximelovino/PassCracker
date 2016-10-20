#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STR_SIZE
#define STR_SIZE 128
#endif
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
	int* length = malloc(sizeof(int));
	char* range = createCharRange("range.txt",length);
	printf("%d chars, range: |||%s|||\n",*length, range );
	if (range[*length-1]=='\n') {
		printf("it's a carriage return\n");
	}
	return 0;
}
