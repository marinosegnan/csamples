#include "strutture.h"

#include <stdlib.h>
#include <string.h>

int comparefun(Cammino* c1, Cammino* c2) { return c1->dist - c2->dist; }

elem buff[10000];  // 10K preallocati
int indici[10000];
int bstart =0;
int bend=10000;

void libera(elem *el){
   indici[bend%10000] = el-buff;
   bend++;
}

elem* creaelem(Cammino* cam, elem *succ)
{
    elem *ret;
    if (bstart <= bend){
        int indice = indici[bstart%10000];
        ret = &buff[indice];
        bstart++;
    }else{
        printf("BUFFER PIENO\n");
        ret = malloc(sizeof(elem));
        exit(1);
    }
    ret->next = succ;
    ret->cammino = cam;
    return ret;
}

void appendi(int elem, intarra* struttura)
{
    if(struttura->size < 200) {
        struttura->val[struttura->size++] = elem;
    } else {
        printf("errore size\n");
        exit(1);
    }
}

zonearra tutte;
Posizione nullaPosizione = { -1, -1, -1 };

zona* creazona(int id, int stato)
{
    for(int i = 0; i < tutte.size; i++) {
        if(tutte.val[i]->id == id) {
            if(tutte.val[i]->stato != stato) {
                printf("errore stato\n");
                exit(1);
            }
            return tutte.val[i];
        }
    }
    zona* ret = malloc(sizeof(zona));
    ret->id = id;
    ret->stato = stato;
    appendz(ret, &tutte);
    return ret;
}

void appendz(zona* elem, zonearra* struttura)
{
    if(struttura->size < 1000) {
        struttura->val[struttura->size++] = elem;
    } else {
        printf("errore size\n");
        exit(1);
    }
}

Cammino* creacammino(Posizione* pos, Cammino* father, int level, int dist)
{
    Cammino* c = (Cammino*)malloc(sizeof(Cammino));
    c->pos = pos;
    c->father = father;
    c->level = level;
    c->dist = dist;
    c->successivi = NULL;
    return c;
}

void insert(listacammini* mialista, Cammino* nuovo)
{
    elem** curr = &(mialista->start);
    int (*confronta)(Cammino * c1, Cammino * c2) = mialista->compare; // ottimizzazione
    while(*curr != NULL && ((*confronta)(nuovo, (*curr)->cammino) >= 0)) {
        curr = &((*curr)->next); 
    }
    elem* e1 = creaelem(nuovo,*curr);
    (*curr) = e1;
    if(e1->next == NULL) {
        mialista->last = e1;
    }
}

void appendc(listacammini* mialista, Cammino* nuovo)
{
    elem* e1 = creaelem(nuovo,NULL);
    if(mialista->last == NULL) {
        mialista->last = e1;
        mialista->start = e1;
    } else {
        mialista->last->next = e1;
        mialista->last = e1;
    }
}

Cammino* next(listacammini* lista)
{
    if(lista == NULL || lista->curr == NULL) {
        return NULL;
    }
    Cammino* ret = lista->curr->cammino;
    lista->curr = lista->curr->next;
    return ret;
}

void start(listacammini* lista) { lista->curr = lista->start; }

Cammino* remov(listacammini* lista)
{
    Cammino* ret = NULL;
    elem* curr = lista->start;
    if(curr != NULL) {
        lista->start = curr->next;
        ret = curr->cammino;
        libera(curr);
    }
    if(lista->start == NULL) {
        lista->last = NULL;
    }
    return ret;
}

listacammini* crealistacammini()
{
    listacammini* ret = malloc(sizeof(listacammini));
    ret->compare = &comparefun;
    ret->start = NULL;
    ret->last = NULL;
    //  ret->size = 0;
    return ret;
}

int distdatarget(Posizione* stato, Posizione* obiettivo)
{
    int d1 = obiettivo->p1 - stato->p1;
    int d2 = obiettivo->p2 - stato->p2;
    int d3 = obiettivo->p3 - stato->p3;
    if(d1 >= 0 && d2 >= 0 && d3 >= 0) {
        return d1 + d2 + d3;
    } else {
        return -1; // oltre il traguardo
    }
}

listaposizioni* crealistaposizioni()
{
    listaposizioni* ret = malloc(sizeof(listaposizioni));
    memset(ret,0,sizeof(listaposizioni));//ret->size = 0;
    return ret;
}

nodo0 fatti;

void inizializza(int size1, int size2, int size3)
{
    fatti.size1 = size1 + 1;
    fatti.size2 = size2 + 1;
    fatti.size3 = size3 + 1;
    fatti.posizioni = malloc(sizeof(nodo1*) * fatti.size1);
    for(int i = 0; i < fatti.size1; i++) {
        fatti.posizioni[i] = NULL;
    }
    for (int i=0; i < 10000;i++){
        indici[i]= i;
    }
}

nodo1* cn1(int sz)
{
    nodo1* ret = malloc(sizeof(nodo1));
    ret->size = sz;
    ret->posizioni = malloc(sizeof(nodo1*) * sz);
    for(int i = 0; i < sz; i++) {
        ret->posizioni[i] = NULL;
    }
    return ret;
}

nodo2* cn2(int sz)
{
    nodo2* ret = malloc(sizeof(nodo2));
    ret->size = sz;
    ret->cammini = malloc(sizeof(Cammino*) * sz);
    for(int i = 0; i < sz; i++) {
        ret->cammini[i] = NULL;
    }
    ret->posizioni = malloc(sizeof(Posizione*) * sz);
    for(int i = 0; i < sz; i++) {
        ret->posizioni[i] = NULL;
    }
    return ret;
}


listacammini* capovolgi(listacammini* inp)
{
    listacammini* ret = crealistacammini();
    Cammino* cc = inp->last->cammino;
    while(cc != NULL) {
        elem* ee = creaelem(cc,ret->start);
      //  ee->next = ret->start;
        ret->start = ee;
        cc = cc->father;
    }
    return ret;
}

void printpath(listacammini* lista)
{
    if(lista == NULL || lista->start == NULL) {
        printf("path VUOTO!\n");
        return;
    }
    elem* ce = lista->start;
    int len = 0;
    while(ce != NULL) {
        Cammino* cc = ce->cammino;
        printf("( %d, %d, %d)\n", cc->pos->p1, cc->pos->p2, cc->pos->p3);
        len += 1;
        ce = ce->next;
    }
    printf("len soluzione %d\n", len);
}

Posizione* creaposizione(int p1, int p2, int p3)
{
    nodo1** n1 = &fatti.posizioni[p1];
    if(*n1 == NULL) {
        *n1 = cn1(fatti.size2);
    }
    nodo2** n2 = &((**n1).posizioni[p2]);
    if(*n2 == NULL) {
        *n2 = cn2(fatti.size3);
    }
    Posizione** ret = &((**n2).posizioni[p3]);
    if(*ret == NULL) {
        Posizione* c = malloc(sizeof(Posizione));
        c->p1 = p1;
        c->p2 = p2;
        c->p3 = p3;
        c->cammino = NULL;
        *ret = c;
    }
    return *ret;
}