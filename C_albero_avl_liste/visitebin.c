#include <stddef.h>
#include <stdio.h>
#include <visitebin.h>

void lbr(nav* navi)
{
    // visita non ricorsiva in preordine un passo alla volta
    // sfrutta il puntatore all' antenato
    // left, base, right

    node* curr = navi->n;
    switch(navi->stato) {
    case DOWN:
        if(curr->left != NULL) {
            navi->n = curr->left;
        } else {
            navi->stato = IO; // fermati e rendi disponibile
        }
        break;
    case IO:
        if(curr->right != NULL) {
            navi->stato = DOWN;
            navi->n = curr->right;
        } else {
            navi->stato = UP;
        }
        break;
    case UP:
        if(curr->up == NULL) {
            navi->n = NULL; // root, fine visita
        } else {
            if(curr->up->left == curr) { // salgo da sx
                navi->stato = IO;        // fermati e rendi disponibile
            } else {
                // salgo da dx
                navi->stato = UP;
            }
            navi->n = curr->up;
        }
        break;
    default:
        printf("next() unknown state %d\n", navi->stato);
        break;
    }
}

void lbrfast(nav* navi)
{
    node* curr = navi->n;
    int stato = navi->stato;
    do {
        switch(stato) {
        case DOWN:
            if(curr->left != NULL) {
                curr = curr->left;
            } else {
                stato = IO; // fermati e rendi disponibile
            }
            break;
        case IO:
            if(curr->right != NULL) {
                stato = DOWN;
                curr = curr->right;
            } else {
                stato = UP;
            }
            break;
        case UP:
            if(curr->up == NULL) {
                curr = NULL;
                stato = IO; // root, fine visita
            } else {
                if(curr->up->left == curr) { // salgo da sx
                    stato = IO;              // fermati e rendi disponibile
                } else {
                    // salgo da dx
                    stato = UP;
                }
                curr = curr->up;
            }
            break;
        default:
            printf("next() unknown state %d\n", navi->stato);
            break;
        }
    } while(stato != IO);
    navi->stato = stato;
    navi->n = curr;
}

void lrb(nav* navi)
{
    // visita non ricorsiva in postordine un passo alla volta
    // sfrutta il puntatore all' antenato
    // left,  right, base

    node* curr = navi->n;
    switch(navi->stato) {
    case DOWN:
        if(curr->left != NULL) {
            navi->n = curr->left;
        } else if(curr->right != NULL) {
            navi->n = curr->right;
        } else {
            navi->stato = IO; // fermati e rendi disponibile
        }
        break;
    case IO:
        navi->stato = UP;
        break;
    case UP:
        if(curr->up == NULL) {
            navi->n = NULL; // root, fine visita
        } else {
            if(curr->up->left == curr && curr->up->right != NULL) {
                // torno su da sx
                navi->n = curr->up->right; // fermati e rendi disponibile
                navi->stato = DOWN;
            } else {
                // salgo da dx
                navi->stato = IO;
                navi->n = curr->up;
            }
        }

        break;
    default:
        printf("next() unknown state %d\n", navi->stato);
        break;
    }
}
void blr(nav* navi)
{
    // visita non ricorsiva da root un passo alla volta
    // sfrutta il puntatore all' antenato
    //  base, left,right

    node* curr = navi->n;
    switch(navi->stato) {
    case IO:
        if(curr->left != NULL) {
            navi->n = curr->left;
        } else {
            navi->stato = DOWN; // fermati e rendi disponibile
        }
        break;
    case DOWN:
        if(curr->right != NULL) {
            navi->stato = IO;
            navi->n = curr->right;
        } else {
            navi->stato = UP;
        }
        break;
    case UP:
        if(curr->up == NULL) {
            navi->n = NULL; // root, fine visita
        } else {
            if(curr->up->left == curr) { // salgo da sx
                navi->stato = DOWN;      // fermati e rendi disponibile
            } else {
                // salgo da dx
                navi->stato = UP;
            }
            navi->n = curr->up;
        }
        break;
    default:
        printf("next() unknown state %d\n", navi->stato);
        break;
    }
}

int next(nav* navi)
{
    // iteratore per visita logica: restituisci i nodi uno alla volta,
    // compiendo anche piu' di un passo, funzione puo' variare
    // puo' essere sostituita da altre visite

    while(navi->n != NULL) {
        navi->fun(navi);
        if(navi->n == NULL) {
            return 0;
        }
        // printf("%d\n",navi->stato);
        if(navi->stato == IO) {
            return 1; // e' il turno del nodo
        }
    }
    return 0;
}

node* nextfast(node* curr, int* state)
{
    // usa algoritmo lbr per iterare
    // il piu' velocemente possibile sull'albero
    int stato = *state;
    do {
        switch(stato) {
        case DOWN:
            if(curr->left != NULL) {
                curr = curr->left;
            } else {
                stato = IO; // fermati e rendi disponibile
            }
            break;
        case IO:
            if(curr->right != NULL) {
                stato = DOWN;
                curr = curr->right;
            } else {
                stato = UP;
            }
            break;
        case UP:
            if(curr->up == NULL) {
                return NULL; // root, fine visita
                             // curr = NULL;
                             //   stato = IO;
            } else {
                if(curr->up->left == curr) { // salgo da sx
                    stato = IO;              // fermati e rendi disponibile
                } else {
                    // salgo da dx
                    stato = UP;
                }
                curr = curr->up;
            }
            break;
        default:
            printf("next() unknown state %d\n", stato);
            break;
        }
    } while(stato != IO);
    *state = stato;
    return curr;
}

node* gotofirst(node* n)
{
    while(n->left != NULL) {
        n = n->left;
    }
    return n;
}

node* nextf(node* curr)
{
    // usa algoritmo lbr per iterare
    // il piu' velocemente possibile sull'albero
    // identica a nextfast() ma non usa parametri perche'
    // parte sempre dallo stato Io, cosi' anche piu' pulita
    // per rcihiami
    int stato = IO;
    node* aux;
    do {
        switch(stato) {
        case DOWN:
            if((aux = curr->left) != NULL) {
                curr = aux;
            } else {
                stato = IO; // fermati e rendi disponibile
            }
            break;
        case IO:
            if((aux = curr->right) != NULL) {
                stato = DOWN;
                curr = aux;
            } else {
                stato = UP;
            }
            break;
        case UP:
            aux = curr->up;
            if(aux == NULL) {
                return NULL; // root, fine visita
            } else {
                if(aux->left == curr) { // salgo da sx
                    stato = IO;         // fermati e rendi disponibile
                } else {
                    // salgo da dx
                    stato = UP;
                }
                curr = aux;
            }
            break;
        default:
            printf("next() unknown state %d\n", stato);
            break;
        }
    } while(stato != IO);
    return curr;
}

void testnaviga0(node* n)
{
    nav navi;
    navi.n = n;
    navi.stato = DOWN;
    navi.fun = lrb;
    printf("test navigazione left right base\n");
    while(next(&navi)) {
        printf("%s\n", tostr(navi.n->elem));
    }
}

void testnaviga1(node* n)
{
    nav navi;
    navi.n = n;
    navi.stato = IO;
    navi.fun = blr;
    printf("test navigazione base left right\n");
    do {
        printf("%s\n", tostr(navi.n->elem));
    } while(next(&navi));
}

void testnaviga2(node* n)
{
    nav navi;
    navi.n = n;
    navi.stato = DOWN;
    navi.fun = lbr;
    printf("test navigazione left base right con funzioni simili a tutte le visite\n");
    while(next(&navi)) {
        ; //   printf("%s\n", tostr(navi.n->elem));
    }
}

void testnaviga3(node* n)
{
    // identico a testnaviga2 ma la funzione di ricerca torna
    // solo ogni volta che serve
    nav navi;
    navi.n = n;
    navi.stato = DOWN;
    navi.fun = lbrfast;
    printf("test navigazione left base right con next uniforme\n");
    while(next(&navi)) {
        ; //   printf("%s\n", tostr(navi.n->elem));
    }
}

void testnaviga4(node* n)
{
    // masssima ottimizzazione: nextfast
    // non rcihiama nulla ma tutto quanto
    int stato = DOWN;
    printf("test navigazione left base right con parametro stato\n");
    node* curr = n;
    while((curr = nextfast(curr, &stato)) != NULL) {
        ; // printf("%s\n", tostr(curr->elem));
    }
}

void testnaviga5(node* n)
{
    // masssima ottimizzazione: nextf
    // non ha neanche parametro stato

    printf("test navigazione left base right senza parametro stato\n");
    // posizionamento al primo nodo della lista
    node* curr = gotofirst(n);
    // oppure :
    //  int stato = DOWN;
    // nextfast(n, &stato);
    while(curr != NULL) {
        // printf("%s\n", tostr(curr->elem));
        curr = nextf(curr);
    }
}

node* elemat(node* n, long pos)
{
    // cerca sequenzialmente nella lista un nodo ad indice N
    // complessita' media N/2
    long curr = 0;
    nav navi;
    navi.n = n;
    navi.stato = DOWN;
    navi.fun = lbr;
    while(next(&navi)) {
        if(curr++ == pos) {
            return navi.n;
        }
    }
    return NULL;
}

node* elempos(node* n, long pos)
{
    // trova elemento ad indice N, usa la dimensione del branch per dirigersi sx o dx
    // complessita': log(N)
    long lsize = n->left == NULL ? 0 : n->left->branchsize;
    if(pos == lsize) {
        return n;
    } else if(pos < lsize) {
        return elempos(n->left, pos);
    } else {
        return elempos(n->right, pos - lsize - 1);
    }
}