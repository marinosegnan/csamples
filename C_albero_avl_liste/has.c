#include <has.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int primi2[] = { 2,  3,  5,  7,  11, 13, 17, 19, 23, 29,  31,  37,  41, 43,
                 47, 59, 67, 71, 73, 83, 87, 93, 97, 101, 103, 107, 109 };
int primi[] = { 2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  59,  67,  71,  73,  83,
                87,  93,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
                191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283 };

int len = (sizeof(primi) / sizeof(primi[0])) - 1;

unsigned long creahash(char* s)
{
    // calcola un hash per una stringa
    unsigned long res = 1;
    // r serve per dare ulteriore variabilita'
    // a stessa lettera in posizioni diverse
    for(int r = 0; *s != '\0'; s++, r++) {
        unsigned int ind = *s - 'a' + r;
        //   if(ind < 0) {
        //        ind = len; // carattere non nelle a..z
        //      }
        res *= primi[ind % len];
    }
    return res; // res < 0 ? -res : res;
}

typedef struct el {
    struct el* next;
    char* s;
    unsigned long hash; // se voglio fare rehashing per cambio dimensione tabella
} elemh;

// 150001 80077 61001 40009 20011
// al rimpicciolire della tabella degrada bene

#define TABE 61001
static elemh* inde[TABE];

int find(char* s)
{
    unsigned long val = creahash(s);
    int index = val % TABE;
    for(elemh* found = inde[index]; found != NULL; found = found->next) {
        if(strcmp(found->s, s) == 0) {
            return index;
        }
    }
    return 0;
}

int addh(char* s)
{
    unsigned long val = creahash(s);
    //  printf("%d\n",val);
    int index = val % TABE;
    elemh* found = NULL;
    for(found = inde[index]; found != NULL; found = found->next) {
        if(strcmp(found->s, s) == 0) {
            //   printf("TROVATO %s\n",s);
            return 0;
        }
    }
    // printf("%s\n",s);
    found = malloc(sizeof(elemh));
    found->next = inde[index];
    found->hash = val;
    found->s = s;
    inde[index] = found;
    return 1;
}

int remh(char* s)
{
    unsigned long val = creahash(s);
    //  printf("%d\n",val);
    int index = val % TABE;
    elemh** base = &inde[index];
    if(*base == NULL) {
        return 0; // non elimino nulla
    }
    elemh* freed = NULL;
    if(strcmp((*base)->s, s) == 0) {
        // il primo
        freed = *base;
        *base = (*base)->next;
    } else {
        elemh* prev = *base;
        while(prev->next != NULL) {
            if(strcmp(prev->next->s, s) == 0) {
                freed = prev->next;
                prev->next = prev->next->next;
                break;
            }
            prev = prev->next;
        }
    }
    if(freed != NULL) {
        free(freed);
        return 1;
    } else {
        return 0;
    }
}

int lenh(int index)
{
    int ret = 0;
    for(elemh* found = inde[index]; found != NULL; found = found->next) {
        ret++;
    }
    return ret;
}

#define ISTO 100
int isto[ISTO];

void stats()
{
    // calcola lunghezza media delle entries
    // della tabella hash

    for(int j = 0; j < TABE; j++) {
        isto[lenh(j)]++;
    }
    long quanti = 0;
    double occupate = 0;
    for(int i = 1; i < ISTO; i++) {
        if(isto[i] != 0) {
            printf("%d ? %d\n", i, isto[i]);
            quanti += isto[i] * i;
            occupate += isto[i];
        }
    }
    printf("Table size %d\n", TABE);
    printf("entries=%ld\n", quanti);
    double av = 0.0;
    for(int i = 1; i < ISTO; i++) {
        if(isto[i] != 0) {
            av += (isto[i] * i * i) / (float)quanti;
        }
    }
    printf("avg. length =%f\n", av);
    printf("crowding =%f\n", occupate / TABE);
}

void testhash() {}
