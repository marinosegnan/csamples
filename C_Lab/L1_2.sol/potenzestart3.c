#include <limits.h>
#include <stdio.h>

static int maxsquare = 0;

int trovamax()
{                                      // qua invece abbiamo a disposizione la moltiplicazione !!!
    for(int i = 0; i < INT_MAX; i++) { // finiremo molto prima
        int j = i * i;
        if(j < 0) {
            return i - 1;
        }
    }
    return INT_MAX;
}

int quadratoOK2(int x) // versione aggiustata
{
    if(maxsquare == 0) {
        maxsquare = trovamax();
    }
    if(x < 0) {
        x = -x;
    }
    if(x > maxsquare) {
        return -1;
    }
    int res = 0;
    for(int i = 0; i < x; i++) {
        res += x;
    }
    return res;
}
