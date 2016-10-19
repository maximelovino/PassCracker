#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

typedef struct BFInfo_t {
  int id;
  int m;
  char* salt;
  char* hash;
  char* range;
} BFInfo;

void* bruteforce(void* arg);

char* nextPass(char* lastPass, BFInfo info);

#endif /* end of include guard: _BRUTEFORCE_H_ */
