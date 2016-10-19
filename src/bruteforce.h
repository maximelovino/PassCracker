#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

typedef struct BFInfo_t {
  int id;
  int m;
  char* salt;
  char* hash;
  const char* range;
  const int rangeLength;
} BFInfo;

typedef struct RangeID_t {
    int* ids;
    int len;
}; RangeID;

void* bruteforce(void* arg);

char* nextPass(char* lastPass, BFInfo info);

#endif /* end of include guard: _BRUTEFORCE_H_ */
