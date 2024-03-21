#include <stdio.h>

typedef struct s1 es1, *es1ptr; // incompleta
es1 a;                          // errore se prima o poi non lo completo
es1ptr b;                       // ok pointer

// se scommento tutto corretto
typedef struct s1 {
    int a;
    double d;
} es1, *es1ptr;

typedef struct s2 {
    double d;
    int a;
} es2, *es2ptr;

void prova(void* ptr, char* tag)
{ // comportamento poco prevedibile ?
    printf("%s come es1: %d %lf\n", tag, ((es1ptr)ptr)->a, ((es1ptr)ptr)->d);
    printf("%s come es2: %d %lf\n", tag, ((es2ptr)ptr)->a, ((es2ptr)ptr)->d);
}

void prova1(es1ptr ptr)
{ // un po' di type checking
    printf("come es1: %d %lf\n", ptr->a, ptr->d);
    // ma se faccio cast tutto inutile
    printf("come cast a es2 (errato):%d %lf\n", ((es2ptr)ptr)->a, ((es2ptr)ptr)->d); // errore !!!!!
}

es1 c1 = { 1, 2.1 };
es2 c2 = { 1.2, 2 };
void* vpo[] = { &c1, &c2 };

void test()
{
    prova(&c1, "es1");
    prova(&c2, "es2");
    prova1(&c1);
    // prova1(&c2);  // errore!!!!
    printf("attraverso void*\n");
    prova(vpo[0], "es1");
    prova(vpo[1], "es2");
}
