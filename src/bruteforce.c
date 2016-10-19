#define _GNU_SOURCE
#include <crypt.h>
#include "bruteforce.h"
#include <stdlib.h>

void* bruteforce(void* arg) {
    BFInfo* info = (BFInfo*) arg;
    int found = 0;
    int* pass = nextPass(NULL, arg);
    char* strPass;
    struct crypt_data* data = malloc(sizeof(struct crypt_data));
    data->initialized = 0;

    while (!found) {
        strPass = rangeToChar(pass, )
        char* hash = crypt_r(pass, arg->salt, data);
        if(strcmp(hash, arg->hash) == 0) {
            found = 1;
        } else {
            pass = nextPass(pass, arg);

        }
    }

    free(data);
    return pass;
}

RangeID* nextPass(RangeID* lastPass, BFInfo* info) {
    if(lastPass != NULL) {
        int newChar = 0;
        int lastID = lastPass->ids[lastPass->len-1];
        lastID += info->m;

        if(lastID > info->rangeLength) {
            lastID -= info->rangeLength;
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
        if(next != NULL) return NULL;
        next->ids = malloc(sizof(int)*(lastPass->len+newChar));
        next->len = lastPass->len+newChar;

        for (int i = 0; i < lastPass->len; i++) {
            next->ids[i+newChar] = lastPass->ids[i];
        }
        if(newChar) {
            next->ids[0] = 0;
        }

        free(lastPass->ids);
        free(lastPass);
    } else {
        //TODO if id > 64 n-letter
        RangeID* next = malloc(sizeof(RangeID));
        next->ids = malloc(sizeof(int));
        next->len = 1;
        next->ids[0] = info->m;
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
