#ifndef ADT_H
#define ADT_H

typedef struct mioadt{
    char *s;
    long num;
    char * (*tof) ();
} adt;

adt* createadt(char *s, int n);

int compare (adt *p, adt *q);

char *tostr(adt*e);

#endif