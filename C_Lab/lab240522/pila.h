#ifndef _PILA_H_
#define _PILA_H_

#include <elements.h>

typedef struct {
    struct elem* top;
    int size;
} pila; //, *pilaptr;

pila* create_pila();
void push(pila* p, void* el);
void* pop(pila* p);
void* top(pila* p);

#endif