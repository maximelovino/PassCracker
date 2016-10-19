#define _GNU_SOURCE
#include <crypt.h>
#include "bruteforce.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void* bruteforce(void* arg) {
printf("LOURD\n");
    BFInfo* info = (BFInfo*) arg;
    int found = 0;
    RangeID* pass = nextPass(NULL, info);
printf(" HAHAHAHA %d\n", pass->ids[0]);
    char* strPass;
    struct crypt_data* data = malloc(sizeof(struct crypt_data));
    data->initialized = 0;

printf("ENTERING LOOP\n");
    while (!found) {
    
        strPass = rangeToChar(pass, info->range);
        
printf("%s\n", strPass);
        
        char* hash = crypt_r(strPass, info->salt, data);
        if(strcmp(hash, info->hash) == 0) {
            found = 1;
        } else {
        
            pass = nextPass(pass, info);

        }
    }

printf("FOUND SHIT\n");
printf("%s\n", strPass);
    free(data);
    return strPass;
}

RangeID* nextPass(RangeID* lastPass, BFInfo* info) {
    if(lastPass != NULL) {
    
        int newChar = 0;
        int lastID = lastPass->ids[lastPass->len-1];
        lastID += info->m;

        if(lastID > info->rangeLength) {
            lastID -= info->rangeLength + 1;
            for (int i = lastPass->len-2; i >= 0; i--) {
                lastPass->ids[i]++;
                if(lastPass->ids[i] < info->rangeLength)
                    break;
                else
                    lastPass->ids[i] = 0;
            }
            if(lastPass->ids[0] >= info->rangeLength) {
                newChar = 1;
            }
        }
        lastPass->ids[lastPass->len-1] = lastID;
        
      

        RangeID* next = malloc(sizeof(RangeID));
        if(next == NULL) return NULL;
        next->ids = malloc(sizeof(int) * (lastPass->len + newChar));
        next->len = lastPass->len+newChar;

        for (int i = 0; i < lastPass->len; i++) {
            next->ids[i+newChar] = lastPass->ids[i];
        }
        if(newChar) {
            next->ids[0] = 0;
        }

        free(lastPass->ids);
        free(lastPass);
        return next;
    } else {
        //TODO if id > 64 n-letter
        RangeID* next = malloc(sizeof(RangeID));
        next->ids = malloc(sizeof(int));
        next->len = 1;
        next->ids[0] = info->id;
        return next;
    }
}

char* rangeToChar(RangeID* id, char* range) {
    char* str = malloc(sizeof(char)*(id->len+1));
    for (int i = 0; i < id->len; i++) {
        str[i] = range[id->ids[i]];
    }
    str[id->len] = 0;
    return str;
}
