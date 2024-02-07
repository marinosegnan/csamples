#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <elements.h>
#include <pila.h>

typedef enum { INIZIO, DOPOUNO, NODO, DOPODUE } nodostato;

#define AVANTI 1
#define INDIETRO -1
#define CORRENTE 0

#define SX -1
#define NOD 0
#define DX 1

typedef pila iterator;

typedef struct {
    pila* p;
    nodostato stato;
} iterators; // con elemento opportuno la pila fa da iteratore per alberi

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

void* next(iterator* ite);
void* prev(iterator* ite);
void* movebf(iterator* ite, int forward);

void* movebfN(iterators* ite, int forward);

#endif