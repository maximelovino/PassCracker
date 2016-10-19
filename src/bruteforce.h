#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

typedef struct BFInfo_t {
  int id;
  int m;
  char* salt;
  char* hash;
  char* range;
  int rangeLength;
} BFInfo;

typedef struct RangeID_t {
    int* ids;
    int len;
} RangeID;

void* bruteforce(void* arg);

RangeID* nextPass(RangeID* lastPass, BFInfo* info);
char* rangeToChar(RangeID* id, char* range);

#endif /* end of include guard: _BRUTEFORCE_H_ */
