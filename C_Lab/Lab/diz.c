
#include "diz.h"

#include "stdlib.h"

#include <stdio.h>
#define SZ 26

manyptr creamany(char val, int sz)
{
    manyptr ret = malloc(sizeof(many));
    if(ret != NULL) {
        if((ret->figli = malloc(sz * sizeof(manyptr))) == NULL) {
            return NULL;
        }
        ret->val = val;
        ret->isword = 0;
        ret->size = sz;
        for(int i = 0; i < sz; i++) {
            ret->figli[i] = NULL;
        }
    }
    return ret;
}

int addword(manyptr m, char* word)
{
    if(*word != '\0') {
        many** place = &(m->figli[*word - 'a']);
        int parola = *(word + 1) == '\0';
        if(*place != NULL) {
            if(parola && (*place)->isword) {
                return 0; // c'era gia'
            }
        } else {
            if((*place = creamany(*word, SZ)) == NULL) {
                return -1;
            }
        }
        if(parola) {
            (*place)->isword = 1;
        } else {
            return addword(*place, word + 1);
        }
    }
    return 1;
}

char bufw[256];
void printmanyn(manyptr m, int level, char* buf)
{
    buf[level] = m->val;
    if(m->isword) {
        buf[level + 1] = '\0';
        printf("%s\n", buf);
    }
    for(int i = 0; i < m->size; i++) {
        if(m->figli[i] != NULL) {
            printmanyn(m->figli[i], level + 1, buf);
        }
    }
}

void printmany(manyptr m)
{
    for(int i = 0; i < m->size; i++) {
        if(m->figli[i] != NULL) {
            printmanyn(m->figli[i], 0, bufw);
        }
    }
}

int testmany()
{

    manyptr uno = creamany('\0', 26);
    printf("%d\n", addword(uno, "aba"));
    printf("%d\n", addword(uno, "cici"));
    printf("%d\n", addword(uno, "aba"));
    printf("%d\n", addword(uno, "coco"));

    printmany(uno);
    return 0;
}
