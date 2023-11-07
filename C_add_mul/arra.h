
#define DIGITS 9

#define MAX(X, Y)  ((X) >( Y) ? (X) : (Y))
#define MIN(X, Y) ((X) <( Y) ? (X) : (Y))
#define DIF(X, Y) ((X) <( Y) ? (Y-X) : (X-Y))

typedef struct myarra{
  //  int digits;  // quante cifre decimali puo' ospitare un singolo numero
    int len;     // max cifre usabili
    int power;   // potenza di digits ** 10 se serve per qualche caso
    int last;    // cifre usate effettivamente
    long *cont;  // array di long che contiene il numero spezzato in digits pezzi
    long base;   // col successivo ci dicono
    long esp;  // in che base il numero e' codicato es 2 ** 4 (=16  decimale)
} arr;

void dumpi( arr*num);
//arr * strtobasebitsfast(char * numerostring, int bits, int digits);
arr* invert(arr * num);

arr * strtobasebits(char * numerostring, int bits, int digits);
arr* create(char* n, int sz, int pow, int base, int esp);
arr* createD(char* n, int sz,int pow, int digits);

arr *fromnumero(arr* orig, int start, int len) ;
arr *fromnumeroP(arr* orig, int start, int len,arr*dest) ;
arr *fromnumeroN(arr* orig, int start, int len ) ;
arr* tobase(arr* numero,int base,int digits);
char * tostr(arr *p);
long fromboin(arr*numero,int quanti);
arr* iszero(arr* x, arr *y);
char *molti(char *s, int intf);
void initzero();
void reset(arr* curr);

void shift(arr* curr,int q);
int greater(arr * nn1,arr*nn2);
