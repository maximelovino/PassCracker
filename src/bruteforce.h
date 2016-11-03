/**
 * Bruteforce header file
 * @file 	bruteforce.h
 * @project	PassCracker
 * @author	Maxime Lovino, Thomas Ibanez, Vincent Tournier
 * @date	November 3, 2016
 */

#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

typedef struct BFInfo_t {
  int id;
  int m;
  char* salt;
  char* hash;
  char* range;
  int rangeLength;
  int* winner;
} BFInfo;

typedef struct RangeID_t {
    int* ids;
    int len;
} RangeID;

void* bruteforce(void* arg);

RangeID* nextPass(RangeID* lastPass, BFInfo* info);
char* rangeToChar(RangeID* id, char* range);
RangeID* genRangeID(int len);
int incrementPass(RangeID* lastPass, BFInfo* info);

#endif /* end of include guard: _BRUTEFORCE_H_ */
