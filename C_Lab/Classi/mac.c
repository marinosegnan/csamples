#include <stdio.h>
#include <string.h>

typedef struct cl {  int (*func)(int);char *name;} cal;
typedef struct mo {  int (*func)(int); int val;cal * lac;}mog,*moptr;

void pippo(){
  // manca da ANSI   printf("%s\n",strupr("pippo"));
    moptr p;
    int v = p->lac->func(3);
}