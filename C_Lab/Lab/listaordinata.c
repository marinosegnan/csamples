#include <assert.h>
#include <listaordinata.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* versioni di lista vera (struct) con/senza HEAD,
 * con attributo contenente la funzione di confronto.
 * la lista cosi' e' un tipo autosufficiente
 * ed utilizza la funzione di confronto attribuita alla creazione
 */

listaordinata* creaordinata(int comparefun(), int head)
{
    listaordinata* ret = malloc(sizeof(listaordinata));
    ret->compare = comparefun;
    ret->start = head == 1 ? crea(NULL) : NULL;
    ret->head = head;
    return ret;
}

void insertho(listaordinata* mialista, void* nuovo)
{
    // con head
    elem* curr = mialista->start;
    int (*confronta)() = mialista->compare; // ottimizzazione
    elem* e;
    while((e = curr->next) != NULL && confronta(nuovo, e->mytype) > 0) {
        curr = e;
    }
    elem* e1 = crea(nuovo);
    e1->next = curr->next;
    curr->next = e1;
}

listaordinata* mergenewh(listaordinata* l1, listaordinata* l2)
{
    listaordinata* ret = creaordinata(l1->compare, 1); // crea copia diritorno
    elem* last = ret->start;
    elem* e1 = l1->start->next;
    elem* e2 = l2->start->next;
    while(e1 != NULL && e2 != NULL) {
        if(l1->compare(e1->mytype, e2->mytype) < 0) {
            last->next = crea(e1->mytype);
            e1 = e1->next;
        } else {
            last->next = crea(e2->mytype);
            e2 = e2->next;
        }
        last = last->next;
    }
    while(e1 != NULL) { // coda della prima
        last->next = crea(e1->mytype);
        e1 = e1->next;
        last = last->next;
    }
    while(e2 != NULL) { // coda della seconda
        last->next = crea(e2->mytype);
        e2 = e2->next;
        last = last->next;
    }
    return ret;
}

listaordinata* mergenew(listaordinata* l1, listaordinata* l2)
{
    // merge di lista senza head
    listaordinata* ret = creaordinata(l1->compare, 0); // crea copia diritorno
    elem** last = &(ret->start);
    elem* e1 = l1->start;
    elem* e2 = l2->start;
    while(e1 != NULL && e2 != NULL) {
        if(l1->compare(e1->mytype, e2->mytype) < 0) {
            *last = crea(e1->mytype);
            e1 = e1->next;
        } else {
            *last = crea(e2->mytype);
            e2 = e2->next;
        }
        last = &(*last)->next;
    }
    while(e1 != NULL) { // copia coda della prima
        *last = crea(e1->mytype);
        e1 = e1->next;
        last = &(*last)->next;
    }
    while(e2 != NULL) { // copia coda della seconda
        *last = crea(e2->mytype);
        e2 = e2->next;
        last = &(*last)->next;
    }
    return ret;
}

void removeho(listaordinata* mialista, void* nuovo)
{
    // con head
    elem* curr = mialista->start;
    int (*confronta)() = mialista->compare; // ottimizzazione
    elem* e;
    while((e = curr->next) != NULL) {
        if(confronta(nuovo, e->mytype) == 0) {
            curr->next = e->next;
            free(e);
            return;
        }
        curr = e;
    }
    printf("element not found\n");
}

void insertno(listaordinata* mialista, void* nuovo)
{
    // no head
    elem* e1 = crea(nuovo);
    if(mialista->start == NULL || mialista->compare(nuovo, mialista->start->mytype) < 0) {
        e1->next = mialista->start;
        mialista->start = e1;
    } else {
        elem* curr = mialista->start;
        elem* e;
        while((e = curr->next) != NULL && mialista->compare(nuovo, e->mytype) > 0) {
            curr = e;
        }
        e1->next = curr->next;
        curr->next = e1;
    }
}

void insertaddrof(listaordinata* mialista, void* nuovo)
{
    //  no head, uso address of & per unificare i casi di primo e successivi
    elem* curr = mialista->start;
    elem** prec = &(mialista->start);
    if(curr != NULL && mialista->compare(nuovo, curr->mytype) > 0) {
        for(elem* e = curr->next; e != NULL && mialista->compare(nuovo, e->mytype) > 0; curr = e, e = e->next) {
            ;
        }
        prec = &curr->next;
    }
    elem* aggiunto = crea(nuovo);
    aggiunto->next = *prec;
    *prec = aggiunto;
}

int findinlist(listaordinata* mialista, void* el)
{
    for(elem* curr = mialista->head ? mialista->start : mialista->start->next; curr != NULL; curr = curr->next) {
        if(mialista->compare(el, curr->mytype) == 0) {
            return 1;
        }
    }
    return 0;
}

void removeo(listaordinata* mialista, void* nuovo)
{
    // senza head
    for(elem *curr = mialista->start, *prev = mialista->start; curr != NULL; prev = curr, curr = curr->next) {
        if(mialista->compare(nuovo, curr->mytype) == 0) {
            if(prev == mialista->start) {
                mialista->start = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
    }
    printf("element not found\n");
}

// seguono altre varianti

void inserto(listaordinata* mialista, void* nuovo)
{
    // no head con break ed un solo richiamo di compare
    elem** prec = &(mialista->start);
    for(elem* curr = mialista->start; curr != NULL; prec = &(curr->next), curr = curr->next) {
        if(mialista->compare(nuovo, curr->mytype) < 0)
            break;
    }
    elem* aggiunto = crea(nuovo);
    aggiunto->next = *prec;
    *prec = aggiunto;
}
