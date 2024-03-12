#include <stdio.h>
#include "tempi.h"

#define BIG 1000 * 1000 * 100
int grande[BIG];

int main(int argc, char** argv)
{
    printf("tempi vari loop\n");
    // riscaldamento,  occorre caricare in memoria il grande array
    miotempo(NULL);
    for(int i = BIG - 1; i >= 0; i--) {
        grande[i] = i;
    }
    miotempo("riscaldamento, carico in memoria");
    
    // ora si puo' confrontare
    for(int i = 0; i < BIG; i++) {
        grande[i] = i;
    }
    miotempo("indice normale");
    
    for(int i = 0; i < BIG; i++) {
        *(grande + i) = i;
    }
    miotempo("indice diverso");

    for(int *q = grande, i = 0, *lim = grande + BIG; q < lim; q++, i++) {
        *q = i;
    }
    miotempo("puntatore");
    
    return 0;
}