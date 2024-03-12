#ifndef DYNSTRING_H
#define DYNSTRING_H

// la dynstring puo' essere creata dinamicamente
// o staicamente . se creata staticamente e' a carico
// dell'utente liberare la memoria sia della strut che dell' area della stringa
// l'utente puo' creare per conto suo tramite malloc etc ed usare solo append

#define MYSIZE(x) (sizeof(x) / sizeof(x[0]))

typedef struct {
    char* content; // vero contenuto
    int capacity;  // spazio disponibile
    int last;      // spazio usato
    int allocated; // tramite malloc
} dynstring, *dynstringptr;

dynstringptr createstring(int capacity);

void append(dynstringptr s, char* s2);

char* tocharstar(dynstringptr p);

int cancelladynstr(dynstringptr p);

void reset(dynstringptr p);

int testdynstring();
char* mydup(char* s, int len); // duplica stringa per len caratteri e aggiunge '\0' finale

#endif
