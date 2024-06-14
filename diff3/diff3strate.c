#include "strutture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

listacammini* trovasequenze(listazone listazone, Posizione* partenza, Posizione* finale, int quantesol)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    listacammini* bestpath = crealistacammini();
    Cammino* root = creacammino(partenza, NULL, 0, 1000000);
    if(!finale) {
        finale = creaposizione(listazone.zone1.size, listazone.zone2.size, listazone.zone3.size);
    }
    listacammini* cammini = crealistacammini();
    insert(cammini, root);
    int cnt = 0;
    int bestsol = 10000000;

    while(cammini->start != NULL && quantesol > 0) {
        Cammino* c = remov(cammini);
        if(c->level + 1 >= bestsol) {
            continue;
        }
        Posizione **disc = c->successivi? &(*(c->successivi))[0]:gruppa(c);
        for(;*disc!= NULL;disc++){
            Posizione* fron = *disc;
            if(memcmp(fron, finale, 3 * sizeof(int)) == 0) {
                Cammino* ca = creacammino(fron, c, c->level + 1, 0);
                fron->cammino = ca;
                cnt++;
                bestsol = ca->level;
                appendc(bestpath, ca);
                quantesol--;
                 //    printf("quante %d\n",quantesol);
            } else {
                Cammino* nodo = fron->cammino; // fron->fatto ? fron->cammino :NULL;//cercacammino(fron) : NULL;
                if(nodo != NULL) {
                    if(nodo->level <= c->level + 1) { // nuovo path al nodo piu lungo
                        continue;
                    }
                    nodo->level = c->level + 1;
                    nodo->father = c;
                    insert(cammini, nodo);
                } else {
                    int dis = distdatarget(fron, finale);
                    Cammino* ca = creacammino(fron, c, c->level + 1, dis);
                    fron->cammino = ca;
                    cnt++;
                    insert(cammini, ca);
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    long mend = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("tempo %f\n", mend / 1000.0);
    return bestpath;
}
