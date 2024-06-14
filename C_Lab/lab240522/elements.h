#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_

typedef struct elem {
    void* mytype;
    struct elem* next;
} elem, *elemptr;

elem* crea(void* content);
// int compareFun(void* e1, void* e2, int fun());

#endif
