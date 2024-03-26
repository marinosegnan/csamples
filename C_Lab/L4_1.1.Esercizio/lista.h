#ifndef LISTA_H
#define LISTA_H

typedef struct s1 {
    int content;
    struct s1* next;
} elem, *elemptr;

typedef struct s2 {
    elem* first;
} lista, *listaptr;

listaptr crealista();

int insert(int val, listaptr l, int index); // inserisce a posizione index

int indexof(int val, listaptr l); // restituisce posizione oppure -1 se manca

char* listtostring(listaptr l); // crea “[ 1 2 3 5 88 ]”

listaptr listfromstring(char* s); //  legge stringa   “[ 1 2 3 5 88 ]”

int test_lista();

void tempi();

#endif
