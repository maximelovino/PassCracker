#define _GNU_SOURCE
#include <crypt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#include "bruteforce.h"


void* bruteforce(void* arg) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    BFInfo* info = (BFInfo*) arg;
    int found = 0;
    RangeID* pass = nextPass(NULL, info);
    char* strPass;
    struct crypt_data* data = malloc(sizeof(struct crypt_data));
    data->initialized = 0;

    while (!found) {

        strPass = rangeToChar(pass, info->range);

//printf("%s\n", strPass);

        char* hash = crypt_r(strPass, info->salt, data);
        if(strcmp(hash, info->hash) == 0) {
            found = 1;
            *(info -> winner) = info -> id;
        } else {
            free(strPass);
            pass = nextPass(pass, info);
        }
    }

    free(data);
    return strPass;
}

RangeID* genRangeID(int len) {
    RangeID* r = malloc(sizeof(RangeID));
    if(r == NULL) return NULL;
    r->ids = malloc(sizeof(int) * len);
    r->len = len;
    return r;
}

RangeID* nextPass(RangeID* lastPass, BFInfo* info) {
    RangeID* next = NULL;

    if(lastPass != NULL) {
        double carry = (double) incrementPass(lastPass, info);

        int nChar = ceil(log(carry+1)/log(info->rangeLength));

        next = genRangeID(lastPass->len+nChar);

        for (int i = nChar; i < lastPass->len+nChar; i++) {
            next->ids[i] = lastPass->ids[i-nChar];
        }

        for(int i = nChar-1; i >= 0; i--) {
            next->ids[i] = ((int)carry-1) % info->rangeLength;
            carry -= info->rangeLength;
        }

        free(lastPass->ids);
        free(lastPass);
        return next;
    } else {
        int size = (int)floor(log(info->id+1)/log(info->rangeLength)) + 1;
        int carry = 0;
        next = genRangeID(size);
        next->ids[next->len-1] = info->id;
        for (int i = next->len-1; i >= 0; i--) {
            next->ids[i] += carry;
            carry = 0;
            while(next->ids[i] >= info->rangeLength) {
                carry++;
                next->ids[i] -= info->rangeLength;
            }
        }
        printf("Thread %i initialized with %s\n", info->id, rangeToChar(next, info->range));
        return next;
    }
}

int incrementPass(RangeID* lastPass, BFInfo* info) {
    int carry = 0;
    lastPass->ids[lastPass->len-1] += info->m;

    for (int i = lastPass->len-1; i >= 0; i--) {
        lastPass->ids[i] += carry;
        carry = 0;
        while(lastPass->ids[i] >= info->rangeLength) {
            carry++;
            lastPass->ids[i] -= info->rangeLength;
        }
        if(carry == 0) break;
    }
    return carry;
}

char* rangeToChar(RangeID* id, char* range) {
    char* str = malloc(sizeof(char)*(id->len+1));
    for (int i = 0; i < id->len; i++) {
        str[i] = range[id->ids[i]];
    }
    str[id->len] = 0;
    return str;
}
