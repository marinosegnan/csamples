#include <bintree.h>
#include <catena.h>
#include <catenaheadord.h>
#include <catenaord.h>
#include <coda.h>
#include <coda2.h>
#include <elements.h>
#include <listaordinata.h>
#include <pila.h>
#include <stdio.h>
#include <tempi.h>

int numeri[100000];

void inizia()
{
    for(int i = 0; i < 100000; i++) {
        numeri[i] = i;
    }
}

void printlistaint(elem* e)
{
    printf("lista:\n");
    while(e != NULL) {
        if(e->mytype == NULL) {
            printf("NULL\n");
        } else {
            printf("%d\n", *(int*)e->mytype);
        }
        e = e->next;
    }
}

int test_coda()
{
    printf("coda\n");
    coda* prova = create_coda();
    append_el(prova, (void*)&numeri[1]);
    append_el(prova, (void*)&numeri[2]);
    append_el(prova, (void*)&numeri[3]);
    printf("size coda = %d\n", prova->size);
    printcoda(prova);
    int* v = remove_el(prova);
    printf("elem coda = %d\n", *v);
    printcoda(prova);
    v = remove_el(prova);
    printf("elem coda = %d\n", *v);
    printcoda(prova);
    v = remove_el(prova);
    printf("elem coda = %d\n", *v);
    printcoda(prova);
    // v = remove_el(prova);
    //    printf("elem coda = %d\n", *v);
    return 0;
}

int test_coda2()
{
    printf("coda2\n");
    coda2* prova = create_coda2();
    append_el2(prova, (void*)&numeri[1]);
    append_el2(prova, (void*)&numeri[2]);
    append_el2(prova, (void*)&numeri[3]);
    printf("size coda = %d\n", prova->size);
    printcoda2(prova);
    int* v = remove_el2(prova);
    printf("elem coda = %d\n", *v);
    printcoda2(prova);
    v = remove_el2(prova);
    printf("elem coda = %d\n", *v);
    printcoda2(prova);
    v = remove_el2(prova);
    printf("elem coda = %d\n", *v);
    printcoda2(prova);
    // v = remove_el(prova);
    //    printf("elem coda = %d\n", *v);
    return 0;
}

int test_pila()
{
    printf("pile\n");
    pila* prova = create_pila();
    int i = 33;
    push(prova, &i);
    printf("size pila = %d\n", prova->size);
    int* v = pop(prova);
    printf("elem pila = %d\n", *v);
    return 0;
}

int test_ric()
{
    printf("ricorsione liste\n");
    elem* e1 = crea(&numeri[8]);
    int* val = e1->mytype; // da qualche parte il cast esplicito ci vuole
    printf("elem lista = %d\n", *val);
    // alternativamente:
    printf("elem lista = %d\n", *(int*)(e1->mytype));
    elem* e2 = crea(&numeri[6]);
    elem* ok = insertbefore(e1, e2, e1);
    elem* e3 = crea(&numeri[7]);
    elem* ok1 = insertbefore(ok, e3, e1);
    printlistaint(ok1 != NULL ? ok1 : ok);
    removel(e2, e1);
    printf("rimuovo 8\n");
    printlistaint(ok1 != NULL ? ok1 : ok);
    return 0;
}

int test_ric_el()
{
    printf("ricorsione liste elementi\n");
    elem* start = crea(&numeri[8]);

    start = insertbeforeel(start, (void*)&numeri[3]);
    start = insertbeforeel(start, (void*)&numeri[5]);
    start = insertbeforeel(start, (void*)&numeri[8]);
    start = insertbeforeel(start, (void*)&numeri[2]);
    start = insertbeforeel(start, (void*)&numeri[2]);
    start = insertbeforeel(start, (void*)&numeri[0]);
    start = insertbeforeel(start, (void*)&numeri[1]);
    start = insertbeforeel(start, (void*)&numeri[2]);
    start = insertbeforeel(start, (void*)&numeri[9]);
    printlistaint(start);
    start = removelel(start, (void*)&numeri[8]);
    start = removelel(start, (void*)&numeri[8]);
    start = removelel(start, (void*)&numeri[8]);
    //   printf("rimuovo 8\n");
    printlistaint(start);
    return 0;
}

int test_ric_el_head()
{
    printf("ricorsione liste elementi\n");
    elem* start = crea(NULL);
    inserth(start, (void*)&numeri[3]);
    inserth(start, (void*)&numeri[5]);
    inserth(start, (void*)&numeri[8]);
    inserth(start, (void*)&numeri[2]);
    inserth(start, (void*)&numeri[2]);
    inserth(start, (void*)&numeri[0]);
    inserth(start, (void*)&numeri[1]);
    inserth(start, (void*)&numeri[2]);
    inserth(start, (void*)&numeri[9]);
    printlistaint(start);
    removeh(start, (void*)&numeri[0]);
    removeh(start, (void*)&numeri[8]);
    removeh(start, (void*)&numeri[8]);
    printlistaint(start);
    return 0;
}

int test_ric_el_head_nr()
{
    printf("non ric liste elementi\n");
    elem* start = crea(NULL);
    inserthnr(start, (void*)&numeri[3]);
    inserthnr(start, (void*)&numeri[5]);
    inserthnr(start, (void*)&numeri[8]);
    inserthnr(start, (void*)&numeri[2]);
    inserthnr(start, (void*)&numeri[2]);
    inserthnr(start, (void*)&numeri[0]);
    inserthnr(start, (void*)&numeri[1]);
    inserthnr(start, (void*)&numeri[2]);
    inserthnr(start, (void*)&numeri[9]);
    printlistaint(start);
    removehnr(start, (void*)&numeri[8]);
    removehnr(start, (void*)&numeri[8]);
    removehnr(start, (void*)&numeri[2]);
    printlistaint(start);
    return 0;
}

int test_el_ord()
{
    printf("lista ordinata\n");
    listaordinata* start = creaordinata(&compareElem, 1);
    insertho(start, (void*)&numeri[3]);
    insertho(start, (void*)&numeri[5]);
    insertho(start, (void*)&numeri[8]);
    insertho(start, (void*)&numeri[2]);
    insertho(start, (void*)&numeri[2]);
    insertho(start, (void*)&numeri[0]);
    insertho(start, (void*)&numeri[1]);
    insertho(start, (void*)&numeri[2]);
    insertho(start, (void*)&numeri[9]);
    printlistaint(start->start);
    removeho(start, (void*)&numeri[8]);
    removeho(start, (void*)&numeri[8]);
    removeho(start, (void*)&numeri[2]);
    printlistaint(start->start);
    return 0;
}

int test_el_ordnoh()
{
    printf("lista ordinata no head\n");
    listaordinata* start = creaordinata(&compareElem, 0);
    inserto(start, (void*)&numeri[3]);
    printlistaint(start->start);
    inserto(start, (void*)&numeri[5]);
    printlistaint(start->start);
    inserto(start, (void*)&numeri[8]);
    inserto(start, (void*)&numeri[2]);
    inserto(start, (void*)&numeri[2]);
    inserto(start, (void*)&numeri[0]);
    inserto(start, (void*)&numeri[1]);
    inserto(start, (void*)&numeri[2]);
    inserto(start, (void*)&numeri[9]);
    printlistaint(start->start);
    removeo(start, (void*)&numeri[8]);
    removeo(start, (void*)&numeri[8]);
    removeo(start, (void*)&numeri[2]);
    printlistaint(start->start);
    return 0;
}
int test_el_tempo()
{
    printf("creo 3 lista 10000 elementi\n");
    listaordinata* start = creaordinata(&compareElem, 0);
    miotempo(NULL);
    for(int i = 0; i < 10000; i++) {
        inserto(start, &numeri[i]);
    }
    miotempo("no head con break");
    start = creaordinata(&compareElem, 0);
    for(int i = 0; i < 10000; i++) {
        insertaddrof(start, &numeri[i]);
    }
    miotempo("no head senza break");
    start = creaordinata(&compareElem, 1);

    for(int i = 0; i < 10000; i++) {
        insertho(start, &numeri[i]);
    }
    miotempo("con head");
    return 0;
}

int test_tree()
{
    //  nodo* nnn = creanodo(&numeri[52], NULL, NULL);
    //    nodo* nn = creanodo(&numeri[51], NULL, nnn);
    nodo* n1 = creanodo(&numeri[3], NULL, NULL);
    nodo* n2 = creanodo(&numeri[5], NULL, NULL);
    nodo* n3 = creanodo(&numeri[4], n1, n2);
    nodo* n4 = creanodo(&numeri[7], NULL, NULL);
    nodo* n5 = creanodo(&numeri[9], NULL, NULL);
    nodo* n6 = creanodo(&numeri[8], n4, n5);
    nodo* n7 = creanodo(&numeri[6], n3, n6);
    preorder(n7);
    printf("post\n");
    postorder(n7);
    printf("preric\n");
    preorderric(n7);
    printf("pila\n");
    inOrder(n7);

    printf("\niteratore\n");
    iterator* it = createit(n7);
    int* n;
    while((n = next(it)) != NULL) {
        printf("%d ", *n);
    }
    printf("\nfine iteratore\n");
    printf("\niteratore back\n");
    it = createit(n7);

    while((n = prev(it)) != NULL) {
        printf("%d ", *n);
    }
    printf("\nfine iteratore\n");
    it = createit(n7);
    printf("\niteratore back/forth\n");
    for(int h = 0; h < 5; h++) {
        n = movebf(it, 1);
        printf("%d\n", *n);
    }
    //  it = createit(n7);
    for(int h = 0; h < 3; h++) {
        n = movebf(it, -1);
        printf("%d\n", *n);
    }
    for(int h = 0; h < 6; h++) {
        if((n = movebf(it, 1)) != NULL) {
            printf("%d\n", *n);

        } else {
            printf("NULL\n");
        }
    }
    /*   for (int h =0;h<4;h++){
           n = move(it,1);
            printf("%d ", *n);
       }*/
    printf("\nfine back/forth\n");
    iterators* its = createitstato(n7);
    printf("\niteratore stato singolo back/forth\n");
    for(int h = 0; h < 5; h++) {
        n = movebfN(its, 1);
        printf("%d\n", *n);
    }
    for(int h = 0; h < 3; h++) {
        n = movebfN(its, -1);
        printf("%d\n", *n);
    }
    for(int h = 0; h < 6; h++) {
        if((n = movebfN(its, 1)) != NULL) {
            printf("%d\n", *n);

        } else {
            printf("NULL\n");
        }
    }
    return 0;
}
int test_insert()
{
    printf("testinsettree\n");
    miotempo("NULL");
    nodo* n1 = creanodo(&numeri[50000], NULL, NULL);
    for(int i = 0; i < 49999; i++) {
        insert(n1, &numeri[i]);
    }
    miotempo("mio");
    n1 = creanodo(&numeri[50000], NULL, NULL);
    for(int i = 0; i < 49999; i++) {
        dam(n1, &numeri[i]);
    }
    miotempo("dam");
    n1 = creanodo(&numeri[50000], NULL, NULL);
    for(int i = 0; i < 49999; i++) {
        damm(n1, &numeri[i]);
    }
    miotempo("damm");

    return 0;
}

int main(int argc, char** argv)
{
    bu();
 /*   inizia();
    test_coda();
    test_pila();
    test_ric();
    test_ric_el();
    test_ric_el_head();
    test_ric_el_head_nr();
    test_coda2();
    test_el_ord();

    test_el_ordnoh();
    test_el_tempo();
    test_tree();
    test_insert();*/
}
