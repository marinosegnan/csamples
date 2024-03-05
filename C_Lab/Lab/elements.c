#include <elements.h>
#include <stdio.h>
#include <stdlib.h>

elem* crea(void* content)
{
    elem* ret = malloc(sizeof(elem));
    ret->next = NULL;
    ret->mytype = content;
    return ret;
}

nodo* creanodo(void* content, nodo* left, nodo* right)
{
    nodo* ret = malloc(sizeof(nodo));
    if(ret == NULL) {
        return NULL;
    }
    ret->left = left;
    ret->right = right;
    ret->mytype = content;
    return ret;
}

int compareElem(void* e1, void* e2)
{
    int a = *(int*)e1;
    int b = *(int*)e2;
    return a - b;
}
