#include <multi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1

molti* creamolti(void* val, int size)
{
    molti* ret = malloc(sizeof(molti));
    // alloco size+1 , cosi' ultimo elemento NULL sempre
    if((ret->figli = malloc(sizeof(molti*) * (size + 1))) == NULL) {
        return NULL;
    }
    molti** curr = ret->figli;
    for(int i = 0; i <= size; i++) {
        *curr++ = NULL;
    }
    ret->size = size;
    ret->val = val;
    return ret;
}

molti* addchild(molti* m, void* val)
{
    molti** curr = m->figli;
    size_t i = 0;
    for(; i < m->size && *curr != NULL; i++, curr++) {
        ;
    }
    if(i == m->size) {
        m->size *= 2;
        m->figli = realloc(m->figli, sizeof(molti*) * (m->size + 1));
        curr = m->figli + m->size / 2;
    }
    if(m->figli != NULL) {
        *curr = creamolti(val, SIZE);
        return *curr;
    } else {
        return NULL; // realloc fallita
    }
}

void printmolti(molti* m, int level)
{
    for(int j = 0; j < level; j++) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "%d\n", *(int*)(m->val));
    molti** curr = m->figli;
    for(int i = 0; i < m->size; i++) {
        if(*curr != NULL) {
            printmolti(*curr, level + 2);
            curr++;
        } else {
            return;
        }
    }
}

void printnodo(nodo* m, int level)
{
    for(int j = 0; j < level; j++) {
        fprintf(stderr, " ");
    }
    if(m == NULL) {
        fprintf(stderr, "NULL\n");
    } else {
        fprintf(stderr, "%d\n", *(int*)(m->mytype));
        printnodo(m->left, level + 2);
        printnodo(m->right, level + 2);
    }
}

nodo* trasf(molti** m) // o molti *m[] se si preferisce
{                      // trasforma da albero n-ario a binario,
    //   i figli del primo vanno a sx
    // i fratelli sono figli destri del primo
    // parametro tutti fratelli sono una array di puntatori a multi
    // questa variante fa un richiamo avuoto, e' piu' elegante???
    return (*m == NULL) ? NULL : creanodo((*m)->val, trasf((*m)->figli), trasf(m + 1));
}

nodo* trasfbig(molti** m)
{
    nodo* ret = creanodo((*m)->val, NULL, NULL);
    molti** curr = (*m)->figli;
    if(*curr != NULL) { // figli
        ret->left = trasf(curr);
    }
    if(*(m + 1) != NULL) { // fratello
        ret->right = trasf(m + 1);
    }
    return ret;
}
