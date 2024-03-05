#ifndef _CODA_H_
#define _CODA_H_

#include <elements.h>

typedef struct {
    struct elem* last;
    int size;
} coda; //, *pilaptr;

coda* create_coda();
void append_el(coda* p, void* el);
void* remove_el(coda* p);
void printcoda(coda* c, char format);

#endif