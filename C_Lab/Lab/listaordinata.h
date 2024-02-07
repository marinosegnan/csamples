#include <elements.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    elem* start;
    int (*compare)(); // confronta due elementi: <0, 0, >0
} listaordinata;

listaordinata* creaordinata(int comparefun(), int head);
void removeho(listaordinata* mialista, void* nuovo);
void insertho(listaordinata* mialista, void* nuovo);
void removeo(listaordinata* mialista, void* nuovo);
void inserto(listaordinata* mialista, void* nuovo);
void insertp(listaordinata* mialista, void* nuovo);
void insertaddrof(listaordinata* mialista, void* nuovo);