#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <elements.h>
#include <pila.h>

/*
#define INDIETRO -1
#define CORRENTE 0
#define AVANTI 1

#define SX -1
#define NODO 0
#define DX 1

 * */
typedef enum { SX, NODO, DX, ROOT, MORE, STOP } Posizione;
typedef enum { INDIETRO, CORRENTE, AVANTI } Direzione;
typedef enum { INIZIO, DOPOUNO, DOPONODO, DOPODUE } Nodostato;
typedef enum { GINI, GUNO, GDUE, GTRE, GFINE } Gnodostato;

typedef pila iterator;

typedef struct {
    pila* p;
    Nodostato stato;
} iterators; // con attributo opportuno la pila fa da iteratore per alberi

typedef struct {
    pila* p;
    Gnodostato stato;
} giterators; // con attributo opportuno la pila fa da iteratore per alberi

void preorder(nodo* root);
void postorder(nodo* root);
void preorderric(nodo* n);
void inOrder(nodo* root);
int insert(nodo* root, void* val);
int insertr(nodo* root, void* val);
int dam(nodo* treePtr, void* value);
int damm(nodo* treePtr, void* value);

iterator* createit(nodo* root);
iterators* createitstato(nodo* root);
giterators* gcreateitstato(nodo* root);

void* next(iterator* ite);
void* nextUnoStato(iterators* ite);
void* prev(iterator* ite);
void* movebf(iterator* ite, Direzione forward);

void* movebfN(iterators* ite, Direzione forward);
void* moveNLR(giterators* ite, Direzione direzione);
void* moveLNR(giterators* ite, Direzione direzione);
void* moveLRN(giterators* ite, Direzione direzione);
void dumps(pila* p);
void dumps1(pila* p);
void diffset(nodo* n1, nodo* n2);
#endif