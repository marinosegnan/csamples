
#include <class.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief minisistema classi ed oggetti, anche le funzioni sono oggetti
 * ovviamente e' complicato farlo solo runtime, non vanno bene i parametri
 * @param c
 */
void stampafunclasse(classe* c)
{
    printf(" classe: %s\n con funzioni:\n", c->name);
    for(int i = 0; i < 10; i++) {
        if(c->funzioni[i] != NULL) {
            printf("%p    %s\n", c->funzioni[i], ((oggettofunzione*)(c->funzioni[i]->ob))->name);
        } else {
            printf("NULL\n");
        }
    }
}

int confronta() { return 0; }

char tmp[] = "                   ";
char* stampaogg(oggetto* val)
{
    sprintf(tmp, " classe %d", *(int*)val);
    return tmp;
}

char* stampa(oggetto* val)
{
    sprintf(tmp, "sono in stampa\n");
    return tmp;
}

char* stampaogg1(oggetto* val)
{
    sprintf(tmp, "classe1 %d", *(int*)val);
    return tmp;
}

char* stampaogg2(oggetto* val)
{
    sprintf(tmp, "classe2 %d", *(int*)val);
    return tmp;
}

char* astringa(oggetto* o)
{ // funzione generica che chiama quella della classe!
    classe* cla = o->myclass;
    return cla->astringa(o->ob);
}

void* esegui(oggetto* o, char* met)
{ // funzione generica che chiama quella della classe!
    classe* cla = o->myclass;
    for(int i = 0; i < 10; i++) {
        if(cla->funzioni[i] != NULL) {
            if(strcmp(cla->funcname[i], met) == 0) {
                oggettofunzione* of = (cla->funzioni[i]->ob); //->metodo;
                return of->metodo(o->ob);
            }
        }
    }
    printf("method %s not found:\n", met);
    return "";
}

classe cl1 = { .name = "classe1", .funzioni = {}, .astringa = stampaogg1, .confronta = confronta };
classe cl2 = { .name = "classe2", .funzioni = {}, .astringa = stampaogg2, .confronta = confronta };
classe funzione = { .name = "funzione", .funzioni = {}, .astringa = stampa, .confronta = confronta };

#define CLAS 10
classe* listaclassi[CLAS];

void iniziaclassi()
{
    listaclassi[0] = &cl1;
    listaclassi[1] = &cl2;
    listaclassi[2] = &funzione;
}

classe* cercaclasse(char* nome)
{
    if(listaclassi[0] == NULL) {
        iniziaclassi();
    }
    for(int i = 0; i < CLAS; i++) {
        if(listaclassi[i] != NULL && strcmp(nome, listaclassi[i]->name) == 0) {
            return listaclassi[i];
        }
    }
    printf("class not found %s\n", nome);
    return NULL;
}

void* creaoggetto(void* elem)
{
    classe* cl11 = malloc(sizeof(classe));
    cl11->astringa = stampaogg1;
    oggetto* ret = malloc(sizeof(oggetto));
    // classe creata a runtime
    classe* c = malloc(sizeof(classe));
    strcpy(c->name, "oggetto");
    c->astringa = stampaogg;
    ret->myclass = c;
    ret->ob = elem;
    return ret;
}

void* creaoggetto1(void* elem, char* clname)
{
    oggetto* ret = malloc(sizeof(oggetto));
    ret->myclass = cercaclasse(clname);
    ret->ob = elem;
    return ret;
}

void* creafunzione(void* elem, char* nam)
{
    oggetto* ret = malloc(sizeof(oggetto));
    ret->myclass = &funzione;
    oggettofunzione* oo = malloc(sizeof(oggettofunzione));
    oo->name = nam;
    oo->metodo = elem;
    ret->ob = oo;
    return ret;
}

void addfunzione(classe* c, oggetto* f, char* funname)
{
    for(int i = 0; i < 10; i++) {
        if(c->funzioni[i] == NULL) {
            c->funzioni[i] = f;
            c->funcname[i] = funname;
            return;
        }
        printf("manca spazio per funzione\n");
    }
}