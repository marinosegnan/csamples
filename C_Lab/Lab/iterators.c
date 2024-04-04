#include <stdio.h>
#include <stdlib.h>

#include "iterators.h"

giterators* gcreateitstato(nodo* root)
{
    giterators* ret = malloc(sizeof(giterators));
    ret->p = create_pila();
    ret->stato = GINI;
    ret->modo = NONE;
    ret->modo = AVANTI;
    push(ret->p, root);
    return ret;
}

giterators* gcreateitmodo(nodo* root, Gmodo modo, Direzione direzione)
{
    giterators* ret = malloc(sizeof(giterators));
    ret->p = create_pila();
    ret->stato = GINI;
    ret->modo = modo;
    ret->direzione = direzione;
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
        return manca; // manca primo figlio, passo al successivo
    }
}

Nodostato fineiter(pila* p, Direzione direzione, Nodostato uno, Nodostato due)
{
    if(p->size == 1) { // root
        return GFINE;
    }
    // vedo se sono un figlio e il senso di visita dice che ci sono altri nodi da visitare
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

void* move(giterators* ite)
{
    //riassume i tre modi di visita, piu' avanti ed indietro
    pila* p = ite->p;
    nodo* curr = top(p);
    Direzione direzione = ite->direzione;
    if(direzione == CORRENTE) {
        return curr; // non spostarti, restituisci nodo corrente
    }
    Gmodo modo = ite->modo;
    for(Gnodostato stato = ite->stato; stato != GFINE; curr = top(p)) {
        switch(stato) {
        case GINI:
            switch(modo) {
            case LNR:
            case LRN:
                stato = transizione(p, direzione == AVANTI ? curr->left : curr->right, GINI, GUNO);
                break;
            case NLR:
                ite->stato = GUNO;
                return curr->mytype;
                break;
                default:break;
            }
            break;
        case GUNO:
            switch(modo) {
            case LNR:
                ite->stato = GDUE;
                return curr->mytype;
                break;
            case NLR:
                stato = transizione(p, direzione == AVANTI ? curr->left : curr->right, GINI, GDUE);
                break;
            case LRN:
                stato = transizione(p, direzione == AVANTI ? curr->right : curr->left, GINI, GDUE);
                break;
                 default:break;
            }
            break;
        case GDUE:
            switch(modo) {
            case LNR:
            case NLR:
                stato = transizione(p, direzione == AVANTI ? curr->right : curr->left, GINI, GTRE);
                break;
            case LRN:
                ite->stato = GTRE;
                return curr->mytype;
                break;
                 default:break;
            }
            break;
        case GTRE: // torno su
            switch(modo) {
            case LNR:
                stato = fineiter(p, direzione, GUNO, GTRE);
                break;
            case NLR:
                stato = fineiter(p, direzione, GDUE, GTRE);
                break;
            case LRN:
                stato = fineiter(p, direzione, GUNO, GDUE);
                break;
                 default:break;
            }
            break;
        case GFINE: // su root fine iterazione
            break;
        }
    }
    glibera(ite);
    return NULL;
}
