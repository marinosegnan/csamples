#ifndef _ITERATORS_H_
#define _ITERATORS_H_

#include "bintree.h"

typedef enum { GINI, GUNO, GDUE, GTRE, GFINE } Gnodostato;
typedef enum { NONE, LNR, NLR, LRN } Gmodo;

typedef struct {
    pila* p;
    Gnodostato stato;
    Gmodo modo;
    Direzione direzione;
} giterators; // con attributo opportuno la pila fa da iteratore per alberi

giterators* gcreateitstato(nodo* root);
giterators* gcreateitmodo(nodo* root, Gmodo modo, Direzione direzione);

void* moveNLR(giterators* ite, Direzione direzione);
void* moveLNR(giterators* ite, Direzione direzione);
void* moveLRN(giterators* ite, Direzione direzione);
void* move(giterators* ite);

#endif