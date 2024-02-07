#include <assert.h>
#include <catenaord.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * verione di lista senza HEAD che pero' lavora sui valori effettivi
 * per esercizio si assume che i valori abbiamo un ordinamento
 * determinato dalla funzione compare(..)
 * e l'inserzione sia quindi ordinata in base ad esso
 * qursta versione permette valori duplicati, volendo si potrebbero
 * impedire realizzando l'implementazione di un set
 */

void insert0el(elem* curr, void* nuovo)
{
    if(curr->next == NULL) { // dopo ultimo
        elem* e = crea(nuovo);
        curr->next = e;
    } else {
        if(compareElem(nuovo, curr->next->mytype) <= 0) {
            elem* e = crea(nuovo);
            e->next = curr->next;
            curr->next = e;
        } else {
            insert0el(curr->next, nuovo);
        }
    }
}

elem* insertbeforeel(elem* start, void* nuovo)
{
    assert(start != NULL);
    if(compareElem(nuovo, start->mytype) <= 0) {
        elem* e = crea(nuovo);
        e->next = start;
        return e;
    } else {
        insert0el(start, nuovo);
        return start;
    }
}

void removelel0(elem* curr, void* nuovo)
{
    if(curr->next == NULL) { // dopo ultimo
        printf("element not found\n");
    } else {
        if(compareElem(nuovo, curr->next->mytype) == 0) {
            elem* e = curr->next;
            curr->next = curr->next->next;
            free(e);
        } else {
            removelel0(curr->next, nuovo);
        }
    }
}

elem* removelel(elem* start, void* target)
{
    assert(start != NULL);
    if(compareElem(target, start->mytype) == 0) { // togli primo
        elem* e = start->next;
        free(start);
        return e;
    } else {
        removelel0(start, target);
    }
    return start;
}