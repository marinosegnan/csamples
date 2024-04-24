#include "dynstring.h"

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

void dumps12(pila* p)
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

static char buf[256] = "";
void stampaint(nodo* n, int inde)
{
    if(n == NULL) {
        return;
    }
    stampaint(n->left, inde + 4);
    for(int i = 0; i < 256; i++)
        buf[i] = ' ';
    sprintf(buf + inde, "%ld", (long)n->mytype);
    printf("%s\n", buf);
    stampaint(n->right, inde + 4);
}

nodo* treefromstring(char** curr)
{
    nodoptr ret1 = NULL;
    nodoptr ret2 = NULL;
    nodoptr ret = NULL;
    long num = -1;
    //  printf("sono a: %s\n",s);
    if(**curr == '(') {
        ++(*curr);
        num = (long*)((**curr) - '0');
        ++(*curr); // una virgola
        ++(*curr); // vai su aperta tonda
        ret1 = treefromstring(curr);
        ++(*curr); // una virgola
        ++(*curr); // vai su aperta tonda
        ret2 = treefromstring(curr);
        ++(*curr); // una chiusa tonda
        ret = creanodo((void*)num, ret1, ret2);
    } else {
        ; // e' NULL, o qualunque carartte non (
    }
    return ret;
}

void recur(dynstringptr s, nodo* n)
{
    char buf[10];
    if(n != NULL) {
        append(s, "("), sprintf(buf, "%ld", (long)(n->mytype));
        append(s, buf);
        append(s, ","), recur(s, n->left);
        append(s, ","), recur(s, n->right);
        append(s, ")");
    } else {
        append(s, "N");
    }
}

char* stringfromtree(nodo* n)
{
    dynstringptr s = createstring(100);
    recur(s, n);
    return tocharstar(s);
}
