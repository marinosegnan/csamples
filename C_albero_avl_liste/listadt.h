#ifndef LISTADT_H
#define LISTADT_H

typedef struct adtel {
  struct adtel *prev;
  struct adtel *next;
  adt *el;
} adelem;

int testlistadt();
int testlistatempi();
int testlistatempiinsertremove();
adelem* add(adelem* p, adt* nuovo);

#endif