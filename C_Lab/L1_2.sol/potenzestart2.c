#include <limits.h>
#include <stdio.h>

#define MAXSQUARE 46340

int quadratoOK(int x) // versione aggiustata
{
    if(x < 0) {
        x = -x;
    }
    if(x > MAXSQUARE) {
        return -1;
    }
    int res = 0;
    for(int i = 0; i < x; i++) {
        res += x;
    }
    return res;
}
