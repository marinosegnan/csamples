#ifndef _DIZ_H
#define _DIZ_H

typedef struct n many, *manyptr;

struct n {
    manyptr* figli;
    int size;
    char val;
    char isword;
};

manyptr creamany(char val, int sz);
int addword(manyptr m, char* word);
void printmany(manyptr m);
int testmany();
void confronta();

#endif