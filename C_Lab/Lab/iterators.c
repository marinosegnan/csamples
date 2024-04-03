

#include "bintree.h"

#include <stdio.h>
#include <stdlib.h>

giterators* gcreateitstato(nodo* root)
{
    giterators* ret = malloc(sizeof(giterators));
    ret->p = create_pila();
    ret->stato = GINI;
    push(ret->p, root);
    return ret;
}

void glibera(giterators* its)
{
    free(its->p);
    free(its);
}

Nodostato transizione(pila* p, nodo* topush, Nodostato celo, Nodostato manca)
{
    if(topush != NULL) {
        push(p, topush);
        return celo;
    } else {
        return manca; // manca primo figlio, passo al nodo
    }
}

Nodostato fineiter(pila* p, Direzione direzione, Nodostato uno, Nodostato due)
{
    if(p->size == 1) { // root
        return GFINE;
    }
    nodo* child = p->top->mytype;
    nodo* parent = p->top->next->mytype;
    int more = (parent->left == child && direzione == AVANTI) || (parent->right == child && direzione == INDIETRO);
    pop(p);
    return more ? uno : due;
}

void* moveLNR(giterators* ite, Direzione direzione)
{
    pila* p = ite->p;
    nodo* curr = top(p);
    if(direzione == CORRENTE) {
        return curr; // non spostarti, restituisci nodo corrente
    }
    for(Gnodostato stato = ite->stato; stato != GFINE; curr = top(p)) {
        switch(stato) {
        case GINI:
            stato = transizione(p, direzione == AVANTI ? curr->left : curr->right, GINI, GUNO);
            break;
        case GUNO:
            ite->stato = GDUE;
            return curr->mytype;
            break;
        case GDUE:
            stato = transizione(p, direzione == AVANTI ? curr->right : curr->left, GINI, GTRE);
            break;
        case GTRE: // torno su
            stato = fineiter(p, direzione, GUNO, GTRE);
            break;
        case GFINE:
            break;
        }
    }
    glibera(ite);
    return NULL;
}

void* moveNLR(giterators* ite, Direzione direzione)
{
    pila* p = ite->p;
    nodo* curr = top(p);
    if(direzione == CORRENTE) {
        return curr; // non spostarti, restituisci nodo corrente
    }
    for(Gnodostato stato = ite->stato; stato != GFINE; curr = top(p)) {
        switch(stato) {
        case GINI:
            ite->stato = GUNO;
            return curr->mytype;
            break;
        case GUNO:
            stato = transizione(p, direzione == AVANTI ? curr->left : curr->right, GINI, GDUE);
            break;
        case GDUE:
            stato = transizione(p, direzione == AVANTI ? curr->right : curr->left, GINI, GTRE);
            break;
        case GTRE: // torno su
            stato = fineiter(p, direzione, GDUE, GTRE);
            break;
        case GFINE:
            break;
        }
    }
    glibera(ite);
    return NULL;
}

void* moveLRN(giterators* ite, Direzione direzione)
{
    pila* p = ite->p;
    nodo* curr = top(p);
    if(direzione == CORRENTE) {
        return curr; // non spostarti, restituisci nodo corrente
    }
    for(Gnodostato stato = ite->stato; stato != GFINE; curr = top(p)) {
        switch(stato) {
        case GINI:
            stato = transizione(p, direzione == AVANTI ? curr->left : curr->right, GINI, GUNO);
            break;
        case GUNO:
            stato = transizione(p, direzione == AVANTI ? curr->right : curr->left, GINI, GDUE);
            break;
        case GDUE:
            ite->stato = GTRE;
            return curr->mytype;
            break;
        case GTRE: // torno su
            stato = fineiter(p, direzione, GUNO, GDUE);
            break;
        case GFINE: // torno su
            break;
        }
    }
    glibera(ite);
    return NULL;
}
