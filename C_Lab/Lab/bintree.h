#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <coda.h>
#include <elements.h>
#include <pila.h>

typedef enum { SX, NODO, DX, ROOT, MORE, STOP } Posizione;
typedef enum { INDIETRO, CORRENTE, AVANTI } Direzione;
typedef enum { INIZIO, DOPOUNO, DOPONODO, DOPODUE } Nodostato;

typedef pila iterator;

typedef struct {
    pila* p;
    Nodostato stato;
} iterators; // con attributo opportuno la pila fa da iteratore per alberi

typedef struct {
    // una struct che contiene un nodo e lo stato associato
    // questa vwrsione ha uno stato per elemento pila, in realta' non serve, basta un solo stato
    char parentesi;
    void* ele;
    coda* elementi;
} nodoparentesi;

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
void* nextUnoStato(iterators* ite);
void* prev(iterator* ite);
void dumps(pila* p);
void diffset(nodo* n1, nodo* n2);

void stampaint(nodo* n, int inde);

nodo* treefromstring(char** s);
char* stringfromtree(nodo* n);
nodoparentesi* parentesi(char** curr);
void stapa(nodoparentesi* np, int level);
#endif