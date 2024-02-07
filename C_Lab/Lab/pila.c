#include <pila.h>
#include <stdio.h>
#include <stdlib.h>

pila* create_pila()
{
    pila* ret = malloc(sizeof(pila));
    if(ret == NULL) {
        printf("malloc error creating pila\n");
        return NULL;
    }
    ret->top = NULL;
    ret->size = 0;
    return ret;
}

void push(pila* p, void* i)
{
    elem* e = crea(i);
    e->next = p->top;
    p->top = e;
    p->size++;
}

void* pop(pila* p)
{
    elem* e = p->top;
    p->top = e->next;
    void* ret = e->mytype;
    free(e);
    p->size--;
    return ret;
}

void* top(pila* p) { return p->top != NULL ? p->top->mytype : NULL; }
