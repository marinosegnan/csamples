#ifndef _STRUTTURE_H
#define _STRUTTURE_H

#include <stdio.h>

typedef struct {
    int id;
    int stato;
} zona;

typedef struct {
    int val[1000];
    int size;
} intarra;

typedef struct {
    zona* val[1000];
    int size;
} zonearra;

void appendi(int elem, intarra* struttura);

zona* creazona(int id, int stato);

void appendz(zona* elem, zonearra* struttura);

// Struttura per contenere i valori delle posizioni
typedef struct p {
    int p1;
    int p2;
    int p3;
    struct c* cammino;
} Posizione;

Posizione* creaposizione(int p1, int p2, int p3);

typedef Posizione * listaposizioni[4];

typedef struct c {
    struct p* pos;
    struct c* father;
    int level;
    int dist;
    listaposizioni* successivi;
} Cammino;

void appendp(Posizione* elem, listaposizioni* struttura);

Cammino* creacammino(Posizione* pos, Cammino* father, int level, int dist);
listaposizioni* crealistaposizioni();

typedef struct elem {
    Cammino* cammino;
    struct elem* next;
} elem;

int comparefun(Cammino* c1, Cammino* c2);

typedef struct {
    elem* start;
    elem* last;
    elem* curr;
    //  int size;
    int (*compare)(Cammino* e1, Cammino* e2); // confronta due elementi: <0, 0, >0
} listacammini;

listacammini* crealistacammini();
elem* creaelem(Cammino* cam, elem *succ);

void insert(listacammini* lista, Cammino* elem);
Cammino* remov(listacammini* lista);

void appendc(listacammini* mialista, Cammino* nuovo);
extern Posizione nullaPosizione;

typedef struct {
    intarra sync1, sync2, sync3;
    zonearra zone1, zone2, zone3;
} listazone;

Posizione ** gruppa(Cammino* camm);

int distdatarget(Posizione* stato, Posizione* obiettivo);

listacammini* trovasequenze(listazone listazone, Posizione* partenza, Posizione* finale, int quantesol);

Cammino* next(listacammini* lista);
void start(listacammini* lista);

typedef struct n2 {
    int size;
    Cammino** cammini;
    Posizione** posizioni;
} nodo2;

typedef struct n1 {
    int size;
    nodo2** posizioni;
} nodo1;

typedef struct n0 {
    int size1, size2, size3;
    nodo1** posizioni;
} nodo0;

extern nodo0 fatti;

void inizializza(int size1, int size2, int size3);

listacammini* capovolgi(listacammini* inp);
void printpath(listacammini* lista);

#endif