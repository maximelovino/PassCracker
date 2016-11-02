#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <crypt.h>


int main(int argc, char const *argv[]) {
  printf("%s", crypt(argv[1],argv[2]));
  return 0;
}
