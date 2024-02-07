#ifndef _CODA2_H_
#define _CODA2_H_

#include <elements.h>

typedef struct {
    struct elem* first;
    struct elem* last;
    int size;
} coda2; //, *pilaptr;

coda2* create_coda2();
void append_el2(coda2* p, void* el);
void* remove_el2(coda2* p);
void printcoda2(coda2* c);

#endif