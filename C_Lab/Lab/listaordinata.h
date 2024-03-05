#include <elements.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    elem* start;
    int head;
    int (*compare)(void* e1, void* e2); // confronta due elementi: <0, 0, >0
} listaordinata;

listaordinata* creaordinata(int comparefun(), int head);
listaordinata* mergenew(listaordinata* l1, listaordinata* l2);
listaordinata* mergenewh(listaordinata* l1, listaordinata* l2);
void removeho(listaordinata* mialista, void* nuovo);
void insertho(listaordinata* mialista, void* nuovo);
void removeo(listaordinata* mialista, void* nuovo);
void inserto(listaordinata* mialista, void* nuovo);
void insertp(listaordinata* mialista, void* nuovo);
void insertaddrof(listaordinata* mialista, void* nuovo);

int findinlist(listaordinata* mialista, void* el);