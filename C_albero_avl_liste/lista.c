#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <adt.h>


typedef struct el {
  struct el *prev;
  struct el *next;
  char *s;
} elem;

elem *add(elem *p, char *nuovo) {
  elem *toadd = (elem *)malloc(sizeof(elem));
  toadd->next = NULL;
  toadd->s = nuovo;
  toadd->prev = p;
  if (p != NULL) {
    p->next = toadd;
  }
  return toadd;
}

elem *addC(elem *head, char *nuovo) {
  elem *toadd = (elem *)malloc(sizeof(elem));
  toadd->s = nuovo;
  if (head == NULL) {
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

char *esempi[] = {"aa", "bb", "cc", "dd", ""};
void main2() {
  // elem * p = add(NULL,"una");

  elem *first = NULL;
  elem *q = NULL;
  for (char **iniz = esempi; **iniz != '\0'; iniz++) {
    q = add(q, *iniz);
    if (first == NULL) {
      first = q;
    }
  }
  elem *last = NULL;
  for (q = first; q != NULL; last = q, q = q->next) {
    printf("%s\n", q->s);
  }
  for (q = last; q != NULL; q = q->prev) {
    printf("%s\n", q->s);
  }
  elem *head = addC(NULL, "");
  for (char **iniz = esempi; **iniz != '\0'; iniz++) {
    addC(head, *iniz);
  }
  printf("%s\n","circolare");
  for (q = head->prev; q != head; q = q->prev) {
    printf("%s\n", q->s);
  }
}