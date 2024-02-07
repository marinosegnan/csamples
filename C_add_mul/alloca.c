#include <miobase.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SP 1000

static arr spazio[SP];
int inizio = 0;
int fine = SP - 1;
arr* posti[SP];
int never = 1;

static long allocati = 0;
static long liberati = 0;

void libera(arr* n, int anche)
{
    if(anche && n->cont != n->iniziali) {
        free(n->cont);
    }
    if(n >= &spazio[0] && n <= &spazio[SP - 1]) {
        fine++;
        posti[fine % SP] = n;
        //  printf("metto al posto%d %x\n",fine%10000,n);
    } else {
#if DEBUG == 6
        printf("USO FREE\n");
#endif
        free(n);
    }
    liberati++;
}
void sistema(arr* num, int newdim)
{
    // cambia dimensione array cifre
    if(newdim > INTERI) {
        long* old = num->cont;
        long* nuovo = malloc(newdim * sizeof(long));
        num->len = newdim;
        memcpy(nuovo, old, num->last * sizeof(long));
        memset(nuovo + num->last, 0, (num->len - num->last) * sizeof(long));
        if(old != num->iniziali) { // gia' allocato da malloc() si puo' liberare
            free(old);
        }
        num->cont = nuovo;
    } else {
        //c'e' spazio non serve riallocare
        num->len = newdim;
    }
}

long* procura(arr* numero, int size)
{
    long* old = numero->cont;
    if(size <= INTERI) {
        numero->cont = numero->iniziali;
    } else {
        numero->cont = malloc(size * sizeof(long));
    }
    return old;
}

int used = 0;
arr* allocarr()
{
    if(SP - (fine - inizio) > used) {
        used = SP - (fine - inizio);
    }
    if(never) {
        for(int i = 0; i < SP; i++) {
            posti[i] = &spazio[i];
        }
        never = 0;
    }
    if(fine - inizio == 0) {
        //   printf("uso malloc\n");
        arr* ret = malloc(sizeof(arr));
        allocati++;
        return ret;
    } else {
        arr* ret = posti[inizio % SP];
        allocati++;
        inizio++;
        return ret;
    }
}

void statis()
{
    printf("allocati, liberati,differenza %ld %ld %ld\n", allocati, liberati, allocati - liberati);
    printf("max arr use: %d\n", used);
}
