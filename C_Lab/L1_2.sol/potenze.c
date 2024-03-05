#include <limits.h>
#include <stdio.h>

#define POT 40

int potenze[POT];

int trovamaxpot(int potenza)
{ // qua invece abbiamo a disposizione la moltiplicazione !!!
    if(potenze[potenza] != 0) {
        return potenze[potenza];
    }
    if(potenza <= 1) {
        potenze[potenza] = INT_MAX;
        return INT_MAX;
    }
    int small = 0;
    int big = INT_MAX;
    for(;;) {
        int curr = (small + big) / 2;
        int stop = 0;
        for(int prevprod = 0, prod = curr, j = 1; j < potenza && !stop; j++) {
            prevprod = prod;
            prod *= curr;
            stop = prod < 0 || prod / curr != prevprod;
        }
        if(stop) {
            big = curr;
        } else {
            small = curr;
        }
        if(big - small == 1) {
            potenze[potenza] = small;
            return small;
        }
        //   printf("small, big, prod %d %d %d\n",small,big, prod);
    }
}

int sommaN(int num, int times)
{
    int res = 0;
    for(int i = 0; i < times; i++) {
        res += num;
    }
    return res;
}

int potenza(int x, int esp)
{
    if(x == 0) {
        return 0;
    }
    int plus = 1;
    if(x < 0) {
        x = -x;
        if(esp % 2 != 0) {
            plus = 0;
        }
    }
    if(x > trovamaxpot(esp)) { //.....
        return -1;
    }
    int res = 1;
    for(int i = 0; i < esp; i++) {
        res = sommaN(res, x);
    }
    return plus ? res : -res;
}

void printpotenze()
{
    printf("POTENZE\n");
    for(int k = 0; k < 40; k++) {
        printf("pot: %d val %d\n", k, trovamaxpot(k));
    }
}