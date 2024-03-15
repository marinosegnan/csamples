#include <stdio.h>

// #define MAXSQUARE 46340

// per convertire un char* in int si puo' usare la funzione
// atoi(char*s) definita in <string.h>

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
