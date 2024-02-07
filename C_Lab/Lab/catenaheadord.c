#include <assert.h>
#include <catenaord.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* versioni lista ordinata (catena con HEAD), ricorsiva e non,
 * con confronto di elemento.
 * queste versioni NON usano una struct per definire un tipo lista
 * esplicito
 */

void inserthnr(elem* start, void* nuovo)
{
    // iterativa con head
    elem* e;
    while((e = start->next) != NULL && compareElem(nuovo, e->mytype) > 0) {
        start = e;
    }
    elem* e1 = crea(nuovo);
    e1->next = start->next;
    start->next = e1;
}

void inserthnr1(elem* start, void* nuovo)
{
    // variazione iterativa meno ottimizzata ? forse il compliatore ottimizza?
    while(start->next != NULL && compareElem(nuovo, start->next->mytype) > 0) {
        start = start->next;
    }
    elem* e1 = crea(nuovo);
    e1->next = start->next;
    start->next = e1;
}

void removehnr(elem* start, void* nuovo)
{
    // iterativa con head
    elem* e;
    while((e = start->next) != NULL) {
        if(compareElem(nuovo, e->mytype) == 0) {
            start->next = e->next;
            free(e);
            return;
        }
        start = e;
    }
    printf("element not found\n");
}

void inserth(elem* start, void* nuovo)
{
    // ricorsiva con head, ci permette di usare una singola funzione
    elem* d = start->next;
    if(d == NULL || compareElem(nuovo, d->mytype) <= 0) {
        elem* e = crea(nuovo);
        e->next = d;
        start->next = e;
    } else {
        inserth(d, nuovo);
    }
}

void removeh(elem* start, void* nuovo)
{
    // ricorsiva con head, ci permette di usare una singola funzione
    elem* d = start->next;
    if(d == NULL) { // dopo ultimo
        printf("element not found\n");
    } else {
        if(compareElem(nuovo, d->mytype) == 0) {
            elem* e = d;
            start->next = e->next;
            free(e);
        } else {
            removeh(d, nuovo);
        }
    }
}
