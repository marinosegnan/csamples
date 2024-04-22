#ifndef _ITERATORS_H_
#define _ITERATORS_H_

#include "bintree.h"

typedef enum { GINI, GUNO, GDUE, GTRE, GFINE } Gnodostato;

// tre modi di visita
//  LNR:  sx,padre,dx
//  NLR:  padre,sx,dx
//  LRN:  sx,dx,padre
typedef enum { NONE, LNR, NLR, LRN } Gmodo;

typedef struct {
    pila* p;
    Gnodostato stato;
    Gmodo modo;
    Direzione direzione;
} giterators; // con attributo opportuno la pila fa da iteratore per alberi

typedef struct {
    long treesize;
    nodo* current;
} costrelem;

typedef struct {
    pila* p;
    long sequence;
} costrstato;

giterators* gcreateit(nodo* root);
giterators* gcreateitmodo(nodo* root, Gmodo modo, Direzione direzione);

costrstato* creatore();

void* moveNLR(giterators* ite, Direzione direzione);
void* moveLNR(giterators* ite, Direzione direzione);
void* moveLRN(giterators* ite, Direzione direzione);
void* move(giterators* ite);

nodo* crealbero();
nodo* crealberocostr();

#endif