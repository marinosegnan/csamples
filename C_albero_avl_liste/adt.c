#include <adt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tostr1(adt* e)
{
    char* t = malloc(strlen(e->s) + 25);
    strcpy(t, e->s);
    char* cur = t + strlen(e->s);
    *cur++ = ' ';
    sprintf(cur, "%ld", e->num);
    return t;
}

adt* createadt(char* s, int n)
{
    adt* nuovo = malloc(sizeof(adt));
    nuovo->s = malloc(sizeof((strlen(s) + 1) * sizeof(char)));
    strcpy(nuovo->s, s);
    nuovo->num = n;
    //  nuovo->tof = tostr1; abbastanza inutile
    return nuovo;
}

int compare(adt* p, adt* q)
{
    if(p == NULL && p == NULL) {
        printf("ADTCOMPARE ERROR NULL\n");
        exit(1);
    }
    if(p == NULL || p == NULL) {
        printf("ADTCOMPARE WITH NULL\n");
    }
    //   NULL e' piu' piccolo di tutti!
    if(p == NULL) {
        return -1;
    }
    if(q == NULL) {
        return 1;
    }
    if(p->num == q->num) {
        return 0;
    } else {
        return p->num < q->num ? -1 : 1;
    }
}

int compareString(adt* p, adt* q)
{
    if(p == NULL || p == NULL) {
        printf("ADTCOMPARE ERROR NULL\n");
        exit(1);
    }
    return strcmp(p->s, q->s);
}

char* tostr(adt* e)
{
    char* t = malloc(strlen(e->s) + 25);
    strcpy(t, e->s);
    char* cur = t + strlen(e->s);
    *cur++ = ' ';
    sprintf(cur, "%ld", e->num);
    return t;
}