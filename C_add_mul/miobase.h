// quale verione usare? si puo' fare la versione generale
// che funziona per qualunque base ed eponente ma e' molto piu' lenta
// se si vuole veloce occorre inserire delle costanti nel codice
// quindi la versione sara':
// se 0 e' generale, se 1 e' per base 10 e 9 DIGITS, se 2 per base 2 e 30 DIGITS

#define VERSIONE 0

#define DIGITS 1

#define MAXNUM 18446744073709551615

#define POTENZA10 1000000000
#define POTENZA1010 1000000000000000000

#define POTENZA2 1073741824
#define POTENZA22 1152921504606846976

#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define DIF(X, Y) ((X) < (Y) ? (Y - X) : (X - Y))
#define INTERI 1000

typedef struct myarra {
    long iniziali[INTERI];
    int len;     // max cifre usabili
    int power;   // potenza di digits ** 10 se serve per qualche caso
    int last;    // cifre usate effettivamente
    long base;   // col successivo ci dicono
    long esp;    // in che base il numero e' codicato es 2 ** 4 (=16 cifre decimali)
    int piccole; // le meno significative sono all'inizio
    long* cont;  // array di long che contiene il numero spezzato in digits pezzi

} arr;

extern long numerozero;
void libera(arr* n, int anche);
arr* allocarr();
long* procura(arr* numero, int size);
void sistema(arr* numero, int size);
void statis();
