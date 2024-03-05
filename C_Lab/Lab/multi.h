#ifndef _MULTI_H_
#define _MULTI_H_

#include <elements.h>

#define SIZE 1
typedef struct m {
    void* val;
    struct m** figli;
    int size;
} molti;

molti* creamolti(void* val, int size);
molti* addchild(molti* m, void* val);
void printmolti(molti* m, int level);
void printnodo(nodo* m, int level);
nodo* trasf(molti** m);

#endif