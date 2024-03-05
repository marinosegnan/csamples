#include <stdio.h>

// #define MAXSQUARE 46340


// funzione errata in alcuni casi...

int quadrato(int x) {
  int ret = 0;
  for (int i = 0; i < x; i++) {
    ret += x;
  }
  return ret;
}

int main(int argc, char *argv[]) { 
    printf("%d\n", quadrato(4)); 
    printf("%d\n", quadrato(-4));
}
