#include <adt.h>
#include <listadt.h>
#include <stdio.h>
#include <stdlib.h>
#include <tempi.h>

adelem* insertord(adelem* p, adt* nuovo)
{
    // inserisci assumendo elementi ordinati, 
    // molto dispendioso per lista lunga
    adelem* succ = p;
    while(succ != NULL && compare(succ->el, nuovo) < 0) {
        succ = succ->next;
    }
    // curr e' il primo successivo, evt NULL
    adelem* toadd = (adelem*)malloc(sizeof(adelem));
    toadd->el = nuovo;
    toadd->next = succ;
    toadd->prev = succ != NULL ? succ->prev : NULL;
    if(toadd->prev != NULL) {
        toadd->prev->next = toadd;
    }
    if(succ != NULL) {
        succ->prev = toadd;
    }
    return toadd;
}

adelem* add(adelem* p, adt* nuovo)
{
    adelem* toadd = (adelem*)malloc(sizeof(adelem));
    toadd->next = NULL;
    toadd->el = nuovo;
    toadd->prev = p;
    if(p != NULL) {
        p->next = toadd;
    }
    return toadd;
}

adelem* elpos(adelem* head, long index)
{
    if(index == 0) {
        return head;
    }
    long count = 0;
    while(count < index) {
        if((head = head->next) == NULL) {
            return NULL;
        }
        count++;
    }
    return head;
}

adelem* appendCircolare(adelem* head, adt* nuovo)
{
    adelem* toadd = (adelem*)malloc(sizeof(adelem));
    toadd->el = nuovo;
    if(head == NULL) {
        // primo elemento
        toadd->next = toadd;
        toadd->prev = toadd;
    } else {
        // aggiungi al fondo e attacca a head
        toadd->prev = head->prev;
        head->prev->next = toadd;
        toadd->next = head;
        head->prev = toadd;
    }
    return toadd;
}

char* esempi[] = { "aa", "bb", "cc", "dd", "" };

int testlistadt()
{
    // elem * p = add(NULL,"una");

    adelem* first = NULL;
    adelem* q = NULL;
    for(char** iniz = esempi; **iniz != '\0'; iniz++) {
        q = add(q, createadt(*iniz, iniz - esempi));
        if(first == NULL) {
            first = q;
        }
    }
    adelem* last = NULL;
    printf("lista doppia non circorae avanti\n");
    for(q = first; q != NULL; last = q, q = q->next) {
        printf("%s\n", tostr(q->el));
    }
    printf("lista doppia non circorae indietro\n");
    for(q = last; q != NULL; q = q->prev) {
        printf("%s\n", tostr(q->el));
    }
    adelem* head = appendCircolare(NULL, createadt("", -1));
    for(char** iniz = esempi; **iniz != '\0'; iniz++) {
        appendCircolare(head, createadt(*iniz, iniz - esempi));
    }
    printf("%s\n", "lista circolare indietro");
    for(q = head->prev; q != head; q = q->prev) {
        printf("%s\n", tostr(q->el));
    }
    printf("VIRT %s\n", q->el->tof(q->el));
    return 0;
}

int testlistatempi()
{
    // elem * p = add(NULL,"una");

    adelem* first = NULL;
    adelem* q = NULL;

    char buf[24];
    miotempo(NULL);
    for(int count = 0; count < 100000; count++) {
        sprintf(buf, "%d", count);
        q = add(q, createadt(buf, count));
        if(first == NULL) {
            first = q;
        }
    }
    miotempo("crea lista 100000");
    miotempo(NULL);
    adelem* what = elpos(first, 90000);
    printf("%s\n", tostr(what->el));
    miotempo("cerca el 90000");
    return 0;
}

#define SZ 100000

int testlistatempiinsertremove()
{
    adelem* first = NULL;
    adelem* q = NULL;

    char buf[24];
    miotempo(NULL);
    for(int count = 0; count < SZ; count++) {
        sprintf(buf, "%d", count * 5);
        q = add(q, createadt(buf, count * 5));
        if(first == NULL) {
            first = q;
        }
    }
    miotempo("crea lista 100000");
    miotempo(NULL);
    q = first;
    while (q != NULL){
        q=q->next;
    }
    miotempo("itera lista 100000");
    miotempo(NULL);
    
    for(int count = 0; count < SZ/10; count++) {
        sprintf(buf, "%d", count + 2);
        // printf("%ld\n",count+2);
        insertord(first, createadt(buf, count + 2));
    }
    miotempo("lista inserisci 10000");
    miotempo(NULL);
    adelem* what = elpos(first, 90000);
    printf("%s\n", tostr(what->el));
    miotempo("cerca el 90000");
    return 0;
}