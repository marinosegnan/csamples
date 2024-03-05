#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_

typedef struct elem {
    void* mytype;
    struct elem* next;
} elem, *elemptr,
    **addrptrel; //, lista ,*elemptr;  elem qui e' un alias per struct elem , elemptr e' aggiunto ma non serve

typedef struct binelem {
    void* mytype;
    struct binelem* left;
    struct binelem* right;
} nodo, *nodoptr; /* ,*elemptr;  elem qui e' un alias per struct elem , elemptr e' aggiunto ma non serve*/

elem* crea(void* content);
nodo* creanodo(void* content, nodo* left, nodo* right);
int compareElem(void* e1, void* e2);
// int compareFun(void* e1, void* e2, int fun());

#endif