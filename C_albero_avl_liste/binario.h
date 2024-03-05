#ifndef BINARIO_H
#define BINARIO_H

#include <adt.h>

#define SZ 100000

typedef struct bin {
    adt* elem;
    struct bin* left;
    struct bin* right;
    struct bin* up;  // aggiornato da tutti ma usato solo da visitebin.c
    long height;     // usato solo da avltree.c
    long branchsize; // usato solo da binario.c
} node;

long treeSize(node* curr);
long treeHeight(node* root);
node* createnode(adt* e, node* parent);
int testbinario();
int testbinariolist();
int testbinarioinsertremove();
int testbinarioinsertrandom();
void checkTree(node* n);

node* removeAdt(node* curr, adt* e);
#endif