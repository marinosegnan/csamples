#include "pot.h"

#include "pluto.h"

#include <stdio.h>

#define MYMAX 10000

void printpotenze(int num, int esp)
{
    for(int u = num; u < MYMAX && esp > 0; u = u * num, esp--) {
        printf("%d\n", u);
    }
}

void mah(pluto q) {}
