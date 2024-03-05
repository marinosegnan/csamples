#ifndef VISITEBIN_H
#define VISITEBIN_H

#include <binario.h>

#define DOWN 0
#define IO 1
#define UP 2

typedef struct na {
    node* n;
    int stato;
    void (*fun)();
} nav;

void lrb(nav* navi);
void lbr(nav* navi);
void blr(nav* navi);
void testnaviga0(node* n);
void testnaviga1(node* n);
void testnaviga2(node* n);
void testnaviga3(node* n);
void testnaviga4(node* n);
void testnaviga5(node* n);
int next(nav* navi);
node* elemat(node* n, long pos);
node* elempos(node* n, long pos);

#endif