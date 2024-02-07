#include <assert.h>
#include <lista.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* versione di catena senza HEAD solo ricorsiva che inserisce o elimina un elemento intero
 * cioe' il valore e anche il suo contenitore, di solito
 * si lavora invece con il contenuto.
 * */

void remove0(elem* curr, elem* pos)
{
    if(curr->next == NULL) {
        printf("element not found\n");
    } else {
        if(curr->next == pos) { // rimuovi
            curr->next = pos->next;
            free(pos);
        } else {
            remove0(curr->next, pos);
        }
    }
}

elem* removel(elem* start, elem* curr)
{
    assert(start != NULL);
    if(start == curr) { // rimuovi primo elem
        elem* ret = start->next;
        free(start);
        return ret;
    } else {
        remove0(start, curr);
        return start;
    }
}

void insert0(elem* curr, elem* nuovo, elem* pos)
{
    if(curr == NULL) {
        printf("element not found\n");
    } else {
        if(curr->next == pos) { // posto giusto
            nuovo->next = pos;
            curr->next = nuovo;
        } else {
            insert0(curr->next, nuovo, pos);
        }
    }
}

elem* insertbefore(elem* start, elem* nuovo, elem* pos)
{
    assert(start != NULL);
    if(start == pos) { // prima del primo
        nuovo->next = start;
        return nuovo;
    } else {
        insert0(start, nuovo, pos);
        return start;
    }
}
