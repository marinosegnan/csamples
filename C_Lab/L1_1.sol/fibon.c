#include "fibon.h"

#include <stdio.h>

#define MYMAX 10000
// facciamo finta che pluto serva qui
pluto pp;

void printfibo(int num)
{
    int n1 = 0;
    int n2 = 1;
    int res = 0;
    int cicli = 0;
    while(cicli < num && res < MYMAX) {
        printf("%d\n", res);
        res = n1 + n2;
        n1 = n2;
        n2 = res;
        cicli++;
    }
    printf("\n");
}

void blah(pluto) {}
