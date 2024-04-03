#include <assert.h>
#include <bintree.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// veriosni iterative, quelle ricorsive sono molto piu' semplici, notare anche che
// se la'lbero e' bilanciato, un albero di profondita' 100 (chiamate ricorsive) puo' contenere 2**100
// nodi, cioe' circa 10**30
// anche versione iteratore back and forth: vedi movebfN()
// tramite iteratore sipuo' confrontare  cose differenti,
// es pezzo di sottoalbero con lista, con determinata lunghezza

typedef struct {
    // una struct che contiene un nodo e lo stato associato
    // questa vwrsione ha uno stato per elemento pila, in realta' non serve, basta un solo stato
    nodo* n;
    int state;
} nodestate;

void dumps(pila* p)
{
    // funziona per interi
    printf("PILA\n");
    elem* dd = p->top;
    while(dd != NULL) {
        nodestate* child = (nodestate*)dd->mytype;
        printf("%d   %d\n", *(int*)child->n->mytype, child->state);
        dd = dd->next;
    }
}

void dumps1(pila* p)
{
    // funziona per interi
    printf("PILA\n");
    elem* dd = p->top;
    while(dd != NULL) {
        nodo* child = (nodo*)dd->mytype;
        printf("%d\n", *(int*)child->mytype);
        dd = dd->next;
    }
}

void preorderric(nodo* n)
{
    // intuitiva, basta cambiare ordine per creare tutte le varianti
    // ma come creare un iteratore??

    if(n != NULL) {
        preorderric(n->left);
        printf("%d\n", *(int*)n->mytype);
        preorderric(n->right);
    }
}

iterators* createitstato(nodo* root)
{
    iterators* ret = malloc(sizeof(iterators));
    ret->p = create_pila();
    ret->stato = INIZIO;
    push(ret->p, root);
    return ret;
}

void libera(iterators* its)
{
    free(its->p);
    free(its);
}

Posizione more(pila* p, int direzione)
{
    // indica se ci sono ancora figli da esaminare a seconda se andiamo
    // avanti o indietro. senza avere bisogno di puntatore al padre,
    // basta vedere se siamo discendenti sx o dx, questo ci dice che se siamo
    // a sx e andiamo avanti, dobbiamo visitare il dx e viceversa se andiamo indietro

    if(p->size > 1) {
        nodo* child = p->top->mytype;
        nodo* parent = p->top->next->mytype;
        if(parent->left == child) {
            return SX;
        } else if(parent->right == child) {
            return DX;
        } else {
            printf("IMPOSSIBILE\n");
            return -1;
        }
    } else { // siamo su root
        return CORRENTE - direzione;
    }
}

void* movebfN(iterators* ite, Direzione direzione)
{

    /* iteratore avanti e indietro ed elemento sul posto (0,1,2)
     * immaginado che l'albero sia ordinato, visita gli elementi in ordine crescente o decrescente
     * usa la solita pila ed un enum intero come stato.

     * 0: entro nel nodo dall'alto
     * 1: dopo primo figlio
     * 2: dopo return del nodo
     * 3: dopo secondo figlio (torna su)
     *
     * le operazioni sono simmetriche a seconda che vada avanti o indietro
     * */
    pila* p = ite->p;
    if(direzione == CORRENTE) {
        return top(p); // non spostarti, restituisci nodo corrente
    }
    nodo* curr;
    while((curr = top(p)) != NULL) {
        //   dumps(ite);   stampa debug
        switch(ite->stato) {
        case INIZIO:
            if(direzione == AVANTI) {
                if(curr->left != NULL) {
                    push(p, curr->left);
                } else {
                    ite->stato = DOPOUNO; // manca primo figlio, passo al nodo
                }
            } else {
                if(curr->right != NULL) {
                    push(p, curr->right);
                } else {
                    ite->stato = DOPOUNO; // manca primo figlio, passo al nodo
                }
            }
            break;
        case DOPOUNO:
            ite->stato = DOPONODO;
            return curr->mytype;
            break;
        case DOPONODO:
            if(direzione == AVANTI) {
                if(curr->right != NULL) {
                    push(p, curr->right);
                    ite->stato = INIZIO;
                } else {
                    ite->stato = DOPODUE; // manca secondo figlio, torno su
                }
            } else {
                if(curr->left != NULL) {
                    push(p, curr->left);
                    ite->stato = INIZIO;
                } else {
                    ite->stato = DOPODUE; // manca secondo figlio, torno su
                }
            }
            break;
        case DOPODUE: // torno su
            int ancora = more(p, direzione);
            pop(p);
            nodo* tmp = top(p);
            if(tmp != NULL) {
                ite->stato = direzione == ancora ? DOPODUE : DOPOUNO;
            } else {
                libera(ite);
                return NULL;
            }
            if(ite->stato != DOPOUNO && ite->stato != DOPODUE) {
                printf("ERRORE stato iteratore  %d\n", ite->stato);
            }
            break;
        }
    }
    libera(ite);
    return NULL;
}

int insert(nodo* root, void* val)
{
    if(root == NULL) {
        return -1;
    }
    nodo* tmp = root;
    while(1) {
        if(tmp->mytype == val) {
            return 0;
        }
        if(val < tmp->mytype) {
            if(tmp->left != NULL) {
                tmp = tmp->left;
            } else {
                tmp->left = creanodo(val, NULL, NULL);
                return 1;
            }
        } else {
            if(tmp->right != NULL) {
                tmp = tmp->right;
            } else {
                tmp->right = creanodo(val, NULL, NULL);
                return 1;
            }
        }
    }
}
// codice inserzione di Damiani con &addrof e **

int dam(nodo* treePtr, void* value)
{
    nodo** nodePtrPtr = &treePtr;

    while(*nodePtrPtr != NULL) {
        if(value < (*nodePtrPtr)->mytype) {
            nodePtrPtr = &((*nodePtrPtr)->left);
        } else if(value > (*nodePtrPtr)->mytype) {
            nodePtrPtr = &((*nodePtrPtr)->right);
        } else {
            return 3;
        }
    }
    *nodePtrPtr = creanodo(value, NULL, NULL);
    return 1;
}

// simile a Daminai ma con meno addrof, piu' veloce, come la mia semplice

int damm(nodo* treePtr, void* value)
{
    nodo** nodePtrPtr = &treePtr;

    while(treePtr != NULL) {
        if(value < treePtr->mytype) {
            nodePtrPtr = &(treePtr->left);
            treePtr = treePtr->left;
        } else if(value > treePtr->mytype) {
            nodePtrPtr = &(treePtr->right);
            treePtr = treePtr->right;
        } else {
            return 3;
        }
    }
    *nodePtrPtr = creanodo(value, NULL, NULL);
    return 1;
}
