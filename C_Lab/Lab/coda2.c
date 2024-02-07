#include <coda2.h>
#include <stdio.h>
#include <stdlib.h>

/* versione con due puntatori ai due estremi
 */

coda2* create_coda2()
{
    coda2* ret = malloc(sizeof(coda2));
    if(ret == NULL) {
        printf("malloc error creating coda2\n");
        return NULL;
    }
    ret->last = NULL;
    ret->first = NULL;
    ret->size = 0;
    return ret;
}

void append_el2(coda2* c, void* el)
{
    elem* e = crea(el);
    if(c->last == NULL) { // vuota
        c->first = e;
    } else {
        c->last->next = e;
    }
    c->last = e;
    c->size++;
}

void* remove_el2(coda2* c)
{
    void* ret = NULL;
    if(c->first != NULL) { // non vuota
        elem* remo = c->first;
        ret = remo->mytype;
        c->first = remo->next;
        if(c->first == NULL) { // vuota?
            c->last = NULL;
        }
        free(remo);
        c->size--;
    }
    return ret;
}

void printcoda2(coda2* c)
{
    printf("coda:\n");
    if(c->first == NULL) {
        printf("EMPTY\n");
    } else {
        for(elem* curr = c->first; curr != NULL; curr = curr->next) {
            printf("%d\n", *(int*)curr->mytype);
        }
    }
}