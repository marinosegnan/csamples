#include "lista.h"

#include "tempi.h"

#include <stdio.h>
#include <stdlib.h>

elemptr creaelem(int val)
{
    elemptr el = malloc(sizeof(elem));
    if(el != NULL) {
        el->next = NULL;
        el->content = val;
    }
    return el;
}

listaptr crealista()
{
    listaptr ret = malloc(sizeof(lista));
    if(ret != NULL) {
        ret->first = NULL;
    }
    return ret;
}

int insert(int val, listaptr l, int index)
{ // inserisce a posizione index , -1 se errore
    // con estensione: se index = size, appende al fondo, si potrebbe fare sempre
    // oppure usare -1 per append
    // vari casi: se index -1 ->append al fondo
    //  0 ->in testa
    // qualunque: -> inserisci e da erroe se lascerebbe un buo dopo ultimo elmento
    if(l->first == NULL || index == 0) {
        // tutti i casi di primo elemento
        if(index > 0) {
            return -1;
        }
        elemptr el = creaelem(val);
        el->next = l->first;
        l->first = el;
        return 0;
    }
    elemptr el = l->first;
    elemptr prec = NULL;
    if(index == -1) {
        // vai al fondo
        for(; el != NULL; prec = el, el = el->next) {
            ;
        }
    } else {
        int cursore = 0;
        for(; el != NULL && cursore < index; prec = el, el = el->next, cursore++) {
            ;
        }
         // controlla se per caso inserisco a SIZE esatta
            // che poi equivael ad un append nel caso particolare
            // cioe' se lista lunga 3 . inserire a indice 3 equivael ad append.
            // entrambi creano il QUARTO elemento
        if(el == NULL && cursore != index) {
           // in questo caso vero errore: inserirei a indice completamente fuori, lasciando dei buchi
            return -1;
        }
    }
    elemptr nuovo = creaelem(val);
    nuovo->next = prec->next;
    prec->next = nuovo;
    return 0;
}

int insertp(int val, listaptr l, int index)
{ // funzione identica alla precedente ma itera usando "&"
  // piu' veloce per append a fondo lista, identica per insert a posizione fissa
  // codice piu' elegante??
  // commenti identici ad altra versione
    elemptr* prec = &l->first;
    if(*prec == NULL || index == 0) {
        if(index > 0) {
            return -1;
        }
    } else if(index == -1) {
        while((*prec) != NULL) {
            prec = &(*prec)->next;
        }
    } else {
        int cursore = 0;
        while((*prec) != NULL && cursore < index) {
            prec = &(*prec)->next;
            cursore++;
        }
        if((*prec) == NULL && cursore != index) {
            return -1;
        }
    }
    elemptr nuovo = creaelem(val);
    nuovo->next = *prec;
    *prec = nuovo;
    return 0;
}

int indexof(int val, listaptr l) { return -1; } // restituisce posizione oppure -1 se manca
char buf[100];                                  // brutta temporanea
char* listtostring(listaptr l)
{ // crea “[ 1 2 3 5 88 ]”
    buf[0] = '[';
    buf[1] = ' ';
    int cursor = 2;
    elemptr p = l->first;
    while(p != NULL) {
        buf[cursor++] = p->content + '0';
        buf[cursor++] = ' ';
        p = p->next;
    }
    buf[cursor] = ']';
    return buf;
}

listaptr listfromstring(char* s) { return NULL; } //  legge stringa   “[ 1 2 3 5 88 ]”

int test_lista()
{
    int errors = 0;
    // test 1
    listaptr l = crealista();
    if(l != NULL) {
        if(l->first != NULL) {
            printf("errore creazione\n");
            errors++;
        }
    }
    // test 2
    int esito = insert(9, l, 1);
    if(esito != -1) {
        printf("errore insert indice sbagliato\n");
        errors++;
    }
    // test 3
    esito = insert(8, l, 0);
    if(esito != 0) {
        printf("errore insert indice 0\n");
        errors++;
    }
    printf("lista = %s\n", listtostring(l));
    // test 4
    esito = insert(6, l, 0);
    if(esito != 0) {
        printf("errore insert indice 0\n");
        errors++;
    }
    printf("lista = %s\n", listtostring(l));
    // test 4
    esito = insert(7, l, 1);
    if(esito != 0) {
        printf("errore insert indice 1\n");
        errors++;
    }
    printf("lista = %s\n", listtostring(l));
    // test 4
    esito = insert(9, l, 3);
    if(esito != 0) {
        printf("errore insert indice 0\n");
        errors++;
    }
    printf("lista = %s\n", listtostring(l));
    // test 4
    esito = insert(4, l, -1);
    if(esito != 0) {
        printf("errore insert indice 0\n");
        errors++;
    }
    // test 5
    esito = insert(2, l, 7);
    if(esito != -1) {
        printf("errore insert indice oltre\n");
        errors++;
    }
    // test 5
    esito = insert(5, l, 0);
    if(esito != 0) {
        printf("errore insert indice 0\n");
        errors++;
    }
    printf("lista = %s\n", listtostring(l));
    return errors;
}

void tempi()
{
    // se non ottimizzate tempi equivalenti
    // se ottimizzate la versione insertp() e' piu' veloce nell'append
    // ma identica per indice fisso. 
    // dovendo scegliere una , in media meglio insertp()
    
    listaptr l = crealista();
    listaptr l2 = crealista();
    miotempo(NULL);
    for(int i = 0; i < 10000; i++) {
        insert(5, l, -1);
    }
    miotempo("trad append");

    for(int i = 0; i < 10000; i++) {
        insertp(5, l2, -1);
    }
    miotempo("addrof append");

    for(int i = 0; i < 10000; i++) {
        insert(5, l2, 9000);
    }
    miotempo("trad indice fisso");

    for(int i = 0; i < 10000; i++) {
        insertp(5, l2, 9000);
    }
    miotempo("addrof indice fisso");
}
