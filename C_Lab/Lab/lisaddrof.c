#include <assert.h>
#include <lisaddrof.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * enensima versione che usa addof poitner to element per non dover restituire
 * valori, se inizio lista modificato, spesso si evita
 */

void insertordel0(addrptrel curr, void* nuovo)
{
    if((*curr)->next == NULL) { // dopo ultimo
        elem* e = crea(nuovo);
        (*curr)->next = e;
    } else {
        if(compareElem(nuovo, (*curr)->next->mytype) <= 0) {
            elem* e = crea(nuovo);
            e->next = (*curr)->next;
            (*curr)->next = e;
        } else {
            insertordel0(&((*curr)->next), nuovo);
        }
    }
}

void insertordel(addrptrel start, void* nuovo)
{
    assert(start != NULL);
    if(*start == NULL || compareElem(nuovo, (*start)->mytype) <= 0) {
        elem* e = crea(nuovo);
        e->next = *start;
        *start = e;
    } else {
        insertordel0(start, nuovo);
    }
}

void removeordel0(addrptrel curr, void* nuovo)
{
    if((*curr)->next == NULL) { // dopo ultimo
        printf("element not found\n");
    } else {
        if(compareElem(nuovo, (*curr)->next->mytype) == 0) {
            elem* e = (*curr)->next;
            (*curr)->next = (*curr)->next->next;
            free(e);
        } else {
            removeordel0(&(*curr)->next, nuovo);
        }
    }
}

void removeordel(addrptrel start, void* target)
{
    assert(start != NULL);
    if(compareElem(target, (*start)->mytype) == 0) { // togli primo
        elem* e = (*start)->next;
        free(*start);
        *start = e;
    } else {
        removeordel0(start, target);
    }
}