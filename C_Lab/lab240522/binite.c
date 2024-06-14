
#include "pila.h"

#include <stdio.h>
#include <stdlib.h>

enum stato { INIZIO, DOPOUNO, DOPONODO, DOPODUE };

typedef struct binelem {
    int mytype;
    struct binelem* left;
    struct binelem* right;
} nodo, *nodoptr;

typedef struct {
    enum stato st;
    nodoptr np;
} nstato, *nstatoptr;

nstatoptr creastato(nodoptr n, enum stato s)
{
    nstatoptr ret = malloc(sizeof(nstato));
    ret->st = s;
    ret->np = n;
    return ret;
}

nodo* creanodo(int content, nodo* left, nodo* right)
{
    nodo* ret = malloc(sizeof(nodo));
    if(ret == NULL) {
        return NULL;
    }
    ret->left = left;
    ret->right = right;
    ret->mytype = content;
    return ret;
}

pila * iter(nodo* n)
{
    pila* p = create_pila();
    push(p, creastato(n, INIZIO));
    return p;
}

int next(pila *p){
    
       nstatoptr curr;
    while((curr = top(p)) != NULL) {
        nodoptr np = curr->np;
        switch(curr->st) {
        case INIZIO:
            if(np->left != NULL) {
                push(p, creastato(np->left, INIZIO));
            }
            curr->st = DOPOUNO;

            break;
        case DOPOUNO:
         curr->st = DOPONODO;
            return  np->mytype;
           
            break;
        case DOPONODO:
            if(np->right != NULL) {
                push(p, creastato(np->right, INIZIO));
            }
            curr->st = DOPODUE;
            break;
        case DOPODUE:
            pop(p);
            break;
        default:
            break;
        }
    }
    return -1;
}

void preorder_ite(nodo* n)
{
    pila* p = create_pila();
    push(p, creastato(n, INIZIO));
    nstatoptr curr;
    while((curr = top(p)) != NULL) {
        nodoptr np = curr->np;
        switch(curr->st) {
        case INIZIO:
            if(np->left != NULL) {
                push(p, creastato(np->left, INIZIO));
            }
            curr->st = DOPOUNO;

            break;
        case DOPOUNO:
            printf("%d\n", np->mytype);
            curr->st = DOPONODO;
            break;
        case DOPONODO:
            if(np->right != NULL) {
                push(p, creastato(np->right, INIZIO));
            }
            curr->st = DOPODUE;
            break;
        case DOPODUE:
            pop(p);
            break;
        default:
            break;
        }
    }
}

void pr(nodo* n)
{
    if(n == NULL) {
        return;
    }
    if(n->left != NULL) {
        pr(n->left);
    }
    printf("%d\n", n->mytype);
    if(n->right != NULL) {
        pr(n->right);
    }
}

int main1(int argc, char* argv[])
{
    nodo* n0 = creanodo(0, NULL, NULL);
    nodo* n2 = creanodo(2, NULL, NULL);
    nodo* n1 = creanodo(1, n0, n2);

    nodo* n4 = creanodo(4, NULL, NULL);
    nodo* n6 = creanodo(6, NULL, NULL);
    nodo* n5 = creanodo(5, n4, n6);

    nodo* n3 = creanodo(3, n1, n5);

    //  pr(n3);
  //  preorder_ite(n3);
    pila *p = iter(n3);
    int val;
    while((val= next(p)) != -1){
        printf("%d\n",val);
    }
}
