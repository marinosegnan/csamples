
// int a;     // errore di ridefinizione se incluso in piu’ sorgenti
typedef struct aa *bb, cc; // OK reincluderlo quante volte si vuole
// il seguente da’ errore se incluso piu’ di una volta per .c
// ma non se incluso in <nome.c> differenti una volta sola

typedef struct dd {
    int y;
} ee; // e’ una normale definizione di tipo
