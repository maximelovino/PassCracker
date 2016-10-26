#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <crypt.h>


int main(int argc, char const *argv[]) {
  printf("%s\n", crypt(argv[1],"43"));
  return 0;
}
