
#include "strutture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

listazone lista = {};

void leggidati(char* fname, listazone* ll)
{
    FILE* fp = fopen(fname, "r");
    if(fp == NULL) {
        fprintf(stderr, "file not found %s\n", fname);
        exit(1);
    }
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    int val1, val2;
    char* letti = fgets(buffer, MAX_LENGTH, fp);
    while(letti) {
        if(strncmp(letti, "#zone", strlen("#zone")) == 0) {
            char ch = letti[5];
            while((letti = fgets(buffer, MAX_LENGTH, fp)) != NULL) {
                if(*letti == '#') {
                    break;
                } else {
                    sscanf(letti, "%d%d", &val1, &val2);
                    zona* z = creazona(val1, val2);
                    switch(ch) {
                    case '1':
                        appendz(z, &lista.zone1);
                        break;
                    case '2':
                        appendz(z, &lista.zone2);
                        break;
                    case '3':
                        appendz(z, &lista.zone3);
                        break;
                    }
                }
            }
            printf("fine zona\n");
        } else if(strncmp(letti, "#sync", strlen("#sync")) == 0) {
            char ch = letti[5];
            while((letti = fgets(buffer, MAX_LENGTH, fp)) != NULL) {
                if(*letti == '#') {
                    break;
                } else {
                    sscanf(letti, "%d", &val1);
                    switch(ch) {
                    case '1':
                        appendi(val1, &lista.sync1);
                        break;
                    case '2':
                        appendi(val1, &lista.sync2);
                        break;
                    case '3':
                        appendi(val1, &lista.sync3);
                        break;
                    }
                }
            }
        } else {
            printf("errore file\n");
            exit(1);
        }
    }

    fclose(fp);
}

// Funzione stub per mieornone, da implementare
void mieornone(Posizione* pos, int* i1, int* i2, int* i3, zona** z1, zona** z2, zona** z3)
{
    *z1 = *z2 = *z3 = NULL;
    int p1 = pos->p1;
    int p2 = pos->p2;
    int p3 = pos->p3;
    if(p1 < lista.zone1.size) {
        *i1 = lista.sync1.val[p1];
        if(*i1 < lista.zone1.size) {
            *z1 = lista.zone1.val[*i1];
        }
    } else {
        *i1 = lista.zone1.size;
    }
    if(p2 < lista.zone2.size) {
        *i2 = lista.sync2.val[p2];
        if(*i2 < lista.zone2.size) {
            *z2 = lista.zone2.val[*i2];
        }
    } else {
        *i2 = lista.zone2.size;
    }
    if(p3 < lista.zone3.size) {
        *i3 = lista.sync3.val[p3];
        if(*i3 < lista.zone3.size) {
            *z3 = lista.zone3.val[*i3];
        }
    } else {
        *i3 = lista.zone3.size;
    }
}

// Funzione gruppa
Posizione ** gruppa(Cammino* camm)
{
    int p1, p2, p3;
    zona *z1, *z2, *z3;
    Posizione* pos = camm->pos;
    mieornone(pos, &p1, &p2, &p3, &z1, &z2, &z3);

    int caso = 0;
    if(z1)
        caso += 1;
    if(z2)
        caso += 2;
    if(z3)
        caso += 4;

    listaposizioni* resul = crealistaposizioni();
    camm->successivi = resul;
    Posizione **result = &((*resul)[0]);

    switch(caso) {
    case 7:
        if(z1 == z2 && z1 == z3) {
            if(lista.zone1.val[pos->p1] != z1 || lista.zone2.val[pos->p2] != z2 ||
               lista.zone3.val[pos->p3] != z3) { // Sostituire 1 con la condizione di controllo effettiva
                result[0] = creaposizione(p1, p2, p3);
            } else {
                result[0] = creaposizione(p1 + 1, p2 + 1, p3 + 1);
            }
        } else if(z1 == z2 && z1 != z3) {
            result[0] = creaposizione(p1 + 1, p2 + 1, p3);
            result[1] = creaposizione(p1, p2, p3 + 1);
        } else if(z1 != z2 && z2 == z3) {
            result[0] = creaposizione(p1 + 1, p2, p3);
            result[1] = creaposizione(p1, p2 + 1, p3 + 1);
        } else if(z1 != z2 && z1 == z3) {
            result[0] = creaposizione(p1 + 1, p2, p3 + 1);
            result[1] = creaposizione(p1, p2 + 1, p3);
        } else {
            result[0] = creaposizione(p1 + 1, p2, p3);
            result[1] = creaposizione(p1, p2 + 1, p3);
            result[2] = creaposizione(p1, p2, p3 + 1);
        }
        break;
    case 3:
        if(z1 == z2) {
            result[0] = creaposizione(p1 + 1, p2 + 1, p3);
        } else {
            result[0] = creaposizione(p1 + 1, p2, p3);
            result[1] = creaposizione(p1, p2 + 1, p3);
        }
        break;
    case 5:
        if(z1 == z3) {
            result[0] = creaposizione(p1 + 1, p2, p3 + 1);
        } else {
            result[0] = creaposizione(p1 + 1, p2, p3);
            result[1] = creaposizione(p1, p2, p3 + 1);
        }
        break;
    case 6:
        if(z2 == z3) {
            result[0] = creaposizione(p1, p2 + 1, p3 + 1);
        } else {
            result[0] = creaposizione(p1, p2 + 1, p3);
            result[1] = creaposizione(p1, p2, p3 + 1);
        }
        break;
    case 1:
        result[0] = creaposizione(p1 + 1, p2, p3);
        break;
    case 2:
        result[0] = creaposizione(p1, p2 + 1, p3);
        break;
    case 4:
        result[0] = creaposizione(p1, p2, p3 + 1);
        break;
    default:
        result[0] = creaposizione(lista.zone1.size, lista.zone2.size, lista.zone3.size); 
        break;
    }
    return result;
}

int main()
{
    leggidati("/home/marino/PycharmProjectslab2/lab2/zone.txt", &lista);
    printf("%d %d %d\n", lista.zone1.size, lista.zone2.size, lista.zone3.size);
    inizializza(lista.zone1.size, lista.zone2.size, lista.zone3.size);
    Posizione* partenza = creaposizione(0, 0, 0);
     trovasequenze(lista, partenza, NULL, 100);
    // oppure : listacammini* result = trovasequenze(lista, partenza, NULL, 100);
    // listacammini* capovolta = capovolgi(result);
    //printpath(capovolta);

    //
    //    while ((cc = next(result)) != NULL){
    //               printf("(%d, %d, %d)\n", cc->pos->p1, cc->pos->p2, cc->pos->p3);
    //
    //    }
    //
  //  free(result);
    return 0;
}
