#define _GNU_SOURCE
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#include <crypt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#include "bruteforce.h"

/**
 * Main bruteforce search method
 * @param arg BFInfo pointer
 */
void* bruteforce(void* arg) {
    BFInfo* info = (BFInfo*) arg;
    RangeID* pass = nextPass(NULL, info);
    char* strPass;
    struct crypt_data* data = malloc(sizeof(struct crypt_data));
    data->initialized = 0;

    while (*(info->winner) == -1) {

        strPass = rangeToChar(pass, info->range);

        char* hash = crypt_r(strPass, info->salt, data);
        if(strcmp(hash, info->hash) == 0) {
            *(info->winner) = info->id;
        } else {
            free(strPass);
            pass = nextPass(pass, info);
        }
    }
    free(info);
    free(pass->ids);
    free(pass);
    free(data);
    return strPass;
}

/**
 * Generates a new RangeID pointer
 * @param  len the length of the range string
 * @return     pointer to the new RangeID
 */
RangeID* genRangeID(int len) {
    RangeID* r = malloc(sizeof(RangeID));
    if(r == NULL) return NULL;
    r->ids = malloc(sizeof(int) * len);
    r->len = len;
    for (int i = 0; i < len; i++) {
      r->ids[i] = 0;
    }
    return r;
}

/**
 * Gives the next password for a thread to try
 * @param  lastPass the last password tried or NULL
 * @param  info     thread info
 * @return          new RangeID to try
 */
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
            next->ids[i] += MAX(carry - 1, 0);
            carry = 0;
            while(next->ids[i] >= info->rangeLength) {
                carry++;
                next->ids[i] -= info->rangeLength;
            }
        }
        //printf("Thread %i initialized with %s\n", info->id, rangeToChar(next, info->range));
        return next;
    }
}

/**
 * Increments the last password and propagates the carry if needed
 * @param  lastPass the password to incrementPass
 * @param  info     thread info
 * @return          if the password is too short, the carry to propagate on new characters, 0 otherwise
 */
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

/**
 * Converts a RangeID to a string
 * @param  id    the rangeID to convert
 * @param  range range on which the id applies
 * @return       string version of id
 */
char* rangeToChar(RangeID* id, char* range) {
    char* str = malloc(sizeof(char)*(id->len+1));
    for (int i = 0; i < id->len; i++) {
        str[i] = range[id->ids[i]];
    }
    str[id->len] = 0;
    return str;
}
