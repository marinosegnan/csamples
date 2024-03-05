#include <limits.h>
#include <stdio.h>

static int maxsquare = 0;
int trovamaxbin()
{   // qua invece abbiamo a disposizione la moltiplicazione !!!
    // questa versione rivela un errore cioe' la assunzione che prodotto int signed
    // dia risultato negativo se overflow!!!
    // un escamotage e' vericficare se a*b/b == a
    int small = 0 + 77;
    int big = INT_MAX - 654;
    for(;;) {
        int curr = (small + big) / 2;
        int prod = curr * curr;
        //  printf("divi=%d\n",prod/curr);
        if(prod < 0) { //|| prod / curr != curr) {
            big = curr;
        } else {
            small = curr;
        }
        if(big - small == 1) {
            return small;
        }
        printf("small, big, prod %d %d %d\n", small, big, prod);
    }
}

int quadratoOK3(int x) // versione aggiustata
{
    if(maxsquare == 0) {
        maxsquare = trovamaxbin();
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
