#include <assert.h>
#include <bintree.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// veriosni iterative, quelle ricorsive sono molto piu' semplici, notare anche che
// se la'lbero e' bilanciato, un albero di profondita' 100 (chiamate ricorsive) puo' contenere 2**100
// nodi, cioe' circa 10**30

// anche versione iteratore back and forth: vedi movebfN()

typedef struct {
    // una struct che contiene un nodo e lo stato associato
    // questa vwrsione ha uno stato per elemento pila, in realta' non serve, basta un solo stato
    nodo* n;
    Nodostato state;
} nodestate;

nodestate* cre(nodo* no, int st)
{
    nodestate* ret = malloc(sizeof(nodestate));
    ret->n = no;
    ret->state = st;
    return ret;
}

iterator* createit(nodo* root)
{
    iterator* ret = create_pila();
    push(ret, cre(root, INIZIO));
    return ret;
}

void preorder(nodo* root)
{ // figlio sx, nodo, figlio dx
    pila* p = create_pila();
    push(p, cre(root, INIZIO));
    nodestate* curr;
    while((curr = top(p)) != NULL) {
        switch(curr->state) {
        case INIZIO:
            if(curr->n->left != NULL) {
                push(p, cre(curr->n->left, INIZIO));
            }
            curr->state = DOPOUNO;
            break;
        case DOPOUNO:
            printf("%d\n", *(int*)curr->n->mytype);
            curr->state = DOPONODO;
            break;
        case DOPONODO:
            if(curr->n->right != NULL) {
                push(p, cre(curr->n->right, INIZIO));
            }
            curr->state = DOPODUE;
            break;
        case DOPODUE: // questo case si potrebbe eliminare,  esiste per chiarezza
            pop(p);
            break;
        }
    }
    free(p);
}

void postorder(nodo* root)
{ // figlio sx, figlio dx, nodo
    // struttura identica a preorder, basta cambiare ordine degli stati
    pila* p = create_pila();
    push(p, cre(root, INIZIO));
    nodestate* curr;
    while((curr = top(p)) != NULL) {
        switch(curr->state) {
        case 0:
            if(curr->n->left != NULL) {
                push(p, cre(curr->n->left, INIZIO));
            }
            curr->state = DOPONODO;
            break;
        case DOPOUNO:
            // aggiungete la vostra chiamata preferita
            printf("%d\n", *(int*)curr->n->mytype);
            curr->state = DOPODUE;
            break;
        case DOPONODO:
            if(curr->n->right != NULL) {
                push(p, cre(curr->n->right, INIZIO));
            }
            curr->state = DOPOUNO;
            break;
        case DOPODUE:
            pop(p);
            break;
        }
    }
    free(p);
}

int sinistro(pila* p)
{
    // indica se ancora nodi da esaminare

    if(p->size > 1) {
        nodo* child = p->top->mytype;
        nodo* parent = p->top->next->mytype;
        return parent->left == child;
    } else { // siamo su root
        return 0;
    }
}

void* nextUnoStato(iterators* ite)
{
    // iteratore preordercon uno stato solo, quando troniamo su (pop())
    // se siamo sul sx dobbiamo visitare il nod dx
    // la struttura si puo' generalizzare a previous() e anche a muoversi avanti indietro a piacere
    // cambiando le operazioni dei diversi stati
    pila* p = ite->p;
    nodo* curr;
    while((curr = top(p)) != NULL) {
        switch(ite->stato) {
        case INIZIO:
            if(curr->left != NULL) {
                push(p, curr->left);
            } else {
                ite->stato = DOPOUNO;
            }
            break;
        case DOPOUNO:
            ite->stato = DOPONODO;
            return curr->mytype;
            break;
        case DOPONODO:
            if(curr->right != NULL) {
                push(p, curr->right);
                ite->stato = INIZIO;
            } else {
                ite->stato = DOPODUE;
            }
            break;
        case DOPODUE:
            if(sinistro(p)) {
                ite->stato = DOPOUNO;
            }
            pop(p);
            break;
        }
    }
    free(ite); // manca free dello stack
    return NULL;
}

void diffset(nodo* n1, nodo* n2)
{
    // diff alberi tramite iteratore, assumendo elementi ordinati
    iterators* it1 = createitstato(n1);
    iterators* it2 = createitstato(n2);
    int* c1 = nextUnoStato(it1);
    int* c2 = nextUnoStato(it2);
    while(c1 != NULL && c2 != NULL) {
        int v1 = *c1;
        int v2 = *c2;
        if(v1 == v2) {
            printf("UGUALI % d\n", v1);
            c1 = nextUnoStato(it1);
            c2 = nextUnoStato(it2);
        } else if(v1 < v2) {
            printf("manca in DUE % d\n", v1);
            c1 = nextUnoStato(it1);
        } else {
            printf("manca in UNO % d\n", v2);
            c2 = nextUnoStato(it2);
        }
    }
    while(c1 != NULL) {
        int v1 = *c1;
        printf("manca in DUE % d\n", v1);
        c1 = nextUnoStato(it1);
    }
    while(c2 != NULL) {
        int v2 = *c2;
        printf("manca in UNO % d\n", v2);
        c2 = nextUnoStato(it2);
    }
}

void* next(iterator* ite)
{
    nodestate* curr;
    while((curr = top(ite)) != NULL) {
        switch(curr->state) {
        case INIZIO:
            curr->state = DOPOUNO;
            if(curr->n->left != NULL) {
                push(ite, cre(curr->n->left, INIZIO));
            }
            break;
        case DOPOUNO:
            curr->state = DOPONODO;
            return curr->n->mytype;
            break;
        case DOPONODO:
            curr->state = DOPODUE;
            if(curr->n->right != NULL) {
                push(ite, cre(curr->n->right, INIZIO));
            }
            break;
        case DOPODUE:
            pop(ite);
            break;
        }
    }
    free(ite);
    return NULL;
}

void* prev(iterator* ite)
{
    nodestate* curr;
    while((curr = top(ite)) != NULL) {
        switch(curr->state) {
        case DOPONODO:
            curr->state = DOPODUE;
            if(curr->n->left != NULL) {
                push(ite, cre(curr->n->left, INIZIO));
            }
            break;
        case DOPOUNO:
            curr->state = DOPONODO;
            return curr->n->mytype;
            break;
        case INIZIO:
            curr->state = DOPOUNO;
            if(curr->n->right != NULL) {
                push(ite, cre(curr->n->right, INIZIO));
            }
            break;
        case DOPODUE:
            pop(ite);
            break;
        }
    }
    free(ite);
    return NULL;
}

void inOrder(nodo* root)
{ // da Geeksforgeeks
    // Set current to root of binary tree
    nodo* current = root;
    pila* p = create_pila();
    int done = 0;

    while(!done) {
        // Reach the left most tNode of the current tNode
        if(current != NULL) {
            // Place pointer to a tree node on the stack
            // before traversing the node's left subtree
            push(p, current);
            current = current->left;
        } else {
            // Backtrack from the empty subtree and visit the
            // tNode at the top of the stack; however, if the
            // stack is empty, you are done
            if(p->size > 0) {
                current = pop(p);
                printf("%d ", *(int*)current->mytype);

                // we have visited the node and its left
                // subtree. Now, it's right subtree's turn
                current = current->right;
            } else
                done = 1;
        }
    }
}
