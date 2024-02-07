#include <coda.h>
#include <stdio.h>
#include <stdlib.h>

coda* create_coda()
{
    coda* ret = malloc(sizeof(coda));
    if(ret == NULL) {
        printf("malloc error creating coda\n");
        return NULL;
    }
    ret->last = NULL;
    ret->size = 0;
    return ret;
}

/* versione con singolo puntatore
 * a ultimo elemento, circolare, che a sua volta punta al primo
 */

void append_el(coda* c, void* el)
{
    elem* e = crea(el);
    if(c->last == NULL) { // vuota
        e->next = e;
    } else {
        e->next = c->last->next;
        c->last->next = e;
    }
    c->last = e;
    c->size++;
}

void* remove_el(coda* c)
{
    void* ret = NULL;
    if(c->last != NULL) {
        elem* remo = c->last->next;
        ret = remo->mytype;
        c->last->next = remo->next;
        if(c->last == remo) {
            c->last = NULL;
        }
        free(remo);
        c->size--;
    }
    return ret;
}

void printcoda(coda* c)
{
    printf("coda:\n");
    if(c->last == NULL) {
        printf("EMPTY\n");
    } else {
        elem* curr = c->last->next;
        do {
            printf("%d\n", *(int*)curr->mytype);
            curr = curr->next;
        } while(curr != c->last->next);
    }
}