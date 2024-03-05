#include <assert.h>
#include <includere.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arr* zero()
{
    // serve creare una copia di zero perche' a seconda della sua posizione
    // diventa in realta' uno 0 significativo dentro ad un numero grande
    arr* zero = allocarr();
    zero->power = 0;
    zero->piccole = 1;
    zero->len = 1;
    zero->esp = 1;
    zero->base = 1;
    zero->last = 1;
    zero->cont = zero->iniziali;
    *(zero->cont) = 0;
    return zero;
}

int digits(long base, int esp)
{
    long r1 = pow(base, esp) - 1;
    int c1 = 1;
    while(r1 >= 10) {
        r1 /= 10;
        c1++;
    }
    return c1;
}

int divisore(arr* n)
{
    int digit = digits(n->base, n->esp);
    return pow(n->base, digit);
}

void aggiustaspazio(arr* numero, long b2, long e2)
{
    int c1 = digits(numero->base, numero->esp);
    int c2 = digits(b2, e2);
    if(c1 > c2) { // serve allargare
        int newdim = numero->len * (c1 / c2 + 1);
        sistema(numero, newdim);
    }
}

arr* clona(arr* nume)
{
    arr* numero = allocarr();
    //   numero->cont = nuovo;
    numero->len = nume->len;
    numero->base = nume->base;
    numero->esp = nume->esp;
    numero->power = nume->power;
    numero->last = nume->last;

    procura(numero, nume->len);

    long* q = numero->cont;
    memcpy(q, nume->cont, nume->last * sizeof(long));
    memset(q + nume->last, 0, (nume->len - nume->last) * sizeof(long));
    /*  while(q - nuovo < nume->last) {
          *q++ = *p++;
      }
      while(q - nuovo < nume->len) {
          *q++ = 0;
      }
     */
    return numero;
}

int iszero(arr* x) { return (x->last == 1 && *(x->cont) == 0); }

int positivo(arr* num) { return num->last > 0 && num->cont[0] != 0; }

arr* strtobasebits(char* numerostring, int bits, int digits)
{
    // converti una stringa contenete un numero decimale
    // in sostanza un array di cifre come potenze del 2,
    // utile per calcoli successivi dove molt e div si possono realizzare
    // come shift
    // digits puo' varaire da 1 a 9 , con 9 e' piu' rapido ovviamente
    if(bits > 60 || bits < 1 || digits < 1 || digits > 9) {
        printf("bits/digits %d %d out of range!!\n", bits, digits);
        return NULL;
    }
    arr* numero = create(numerostring, 0, 0, 10, digits);
    arr* ret = cambiabase(numero, 2, bits);
    libera(numero, 1);
    return ret;
}

static long tabella[64];

int verify(arr* m, arr* n)
{
    if(m->piccole != n->piccole) {
        printf("verify: direzione opposta!\n");
        return 1;
    }
    char* s1 = tostr(m);
    char* s2 = tostr(n);
    int lim = strlen(s1);
    int ret = 0;
    for(int i = 0; i < lim; i++) {
        if(s1[i] == s2[i]) {
            if(s1[i] == '(') {
                break;
            }
        } else {
            printf("differnt digit at position=%d ( %c != %c)\n", i, s1[i], s2[i]);
            ret = 1;
        }
    }
    if(ret == 0 && strlen(s2) != lim) {
        ret = 1;
        printf("numbers have differnt length: %d vs. %ld\n", lim, strlen(s2));
    }
    return ret;
}

void fatabella(unsigned long num)
{
    unsigned long curr = num;
    tabella[0] = 1;
    int i = 1;
    while(curr < MAXNUM) {
        tabella[i] = curr;
        curr *= num;
        if(curr < tabella[i]) { // stiamo tornando indietro causa overflow
            for(++i; i < 64; i++) {
                tabella[i] = 0;
            }
            break;
        }
        i++;
    }
}

long trova(long num)
{
    for(int i = 1; i < 64 && tabella[i] != 0; i++) {
        if(tabella[i] > num) {
            return tabella[i - 1];
        }
    }
    printf("ERRORE TABELLA CERCO %ld\n", num);
    return 0;
}

arr* cambiabase(arr* nume, int base, int esponente)
{
    arr* numero = clona(nume);
    unsigned long divisore = pow(base, esponente);
    fatabella(divisore);
    aggiustaspazio(numero, base, esponente);
    invert(numero);
    long fattore = pow(numero->base, numero->esp);
    arr* nuovo = create(NULL, numero->len, 0, numero->base, numero->esp);
    arr* ret = create(NULL, numero->len * 2, 0, base, esponente);
    long* retpt = ret->cont;
    while(positivo(numero)) {
        //  printf("divido: ");
        //  dumpi(numero);
        long* l1 = numero->cont + numero->last;
        long num = 0;
        long* p = nuovo->cont;
        for(long* pos = numero->cont; pos < l1; pos++) {
            num = num * fattore + *pos;
            if(num >= divisore) {
                long ris = num / divisore;
                if(ris >= fattore) {
                    long nu = trova(ris);
                    while(ris >= fattore) {
                        *p++ = ris / nu;
                        ris %= nu;
                        nu /= fattore;
                    }
                } else {
                    *p++ = ris;
                }
            } else {
                if(p - nuovo->cont > 0) {
                    *p++ = 0;
                }
            }
            num = num % divisore;
        }
        nuovo->last = p - nuovo->cont;
        //   dumpi(nuovo);
        arr* temp = numero;
        numero = nuovo;
        nuovo = temp;
        nuovo->last = 0;
        *retpt++ = num;
        //  printf("ret=\n");
        //  ret->last++;
        //  dumpi(ret);
    }
    ret->last = retpt - ret->cont;
    libera(nuovo, 1);
    libera(numero, 1);
    return ret;
}

void dumpi(arr* num)
{
    printf("(base=%ld esp=%ld piccoleprima %d power=%d last=%d len%d)\n", num->base, num->esp, num->piccole, num->power,
           num->last, num->len);
    for(int i = 0; i < num->last; i++) {
        printf("\t%ld\n", (long)num->cont[i]);
    }
}

arr* create(char* n, int sz, int pow, int base, int esp)
{
    arr* ret = allocarr();
    ret->power = pow;
    ret->esp = esp;
    ret->base = base;
    ret->piccole = 1;
    // digits calcolate automaticamente
    // a meno che la base sia 10, alora si puo' specificare quante digits
    int digi = base == 10 ? esp : digits(base, esp);

    if(n != NULL) {
        int quante = strlen(n) / digi; // esp;
        int resto = strlen(n) % digi;  // esp;
        if(resto > 0) {
            quante++;
            resto = digi - resto;
        }
        char nome[quante * digi + 1];
        // riempi a giusta quantita per avre un multiplo
        for(int i = 0; i < resto; i++) {
            nome[i] = ' ';
        }
        strncpy(nome + resto, n, strlen(n));
        nome[quante * digi] = '\0';
        ret->len = quante;

        ret->last = ret->len;
        //  ret->cont = malloc(ret->len * sizeof(long));
        procura(ret, ret->len);
        // crea capovolto, cosi' indici piu' leggibili partendo da 0
        char buf[digi + 1];
        int quanti = strlen(nome);
        char* p = nome + quanti;
        for(int i = 0; i < quante; i++) {
            strncpy(buf, p - (digi * (i + 1)), digi);
            buf[digi] = '\0';
            ret->cont[i] = atol(buf);
        }
    } else {
        // se non do stringa di input, devo specificare quante cifre allocare
        ret->len = sz;
        ret->last = 0;
        procura(ret, ret->len);
        // in questo caso lo azzeriamo non sapendo quanto ne sara' occupato
        memset(ret->cont, 0, ret->len * sizeof(long));
    }
    return ret;
}

arr* invert(arr* num)
{
    long* p = num->cont;
    long* q = p + num->last - 1;
    while(p < q) {
        long tmp = *p;
        *p++ = *q;
        *q-- = tmp;
    }
    num->piccole = 1 - num->piccole;
    return num;
}

int greater(arr* nn1, arr* nn2)
{
    assert(nn1->piccole == 1);
    int sz1 = nn1->last;
    int sz2 = nn2->last;
    int pow1 = nn1->power;
    int pow2 = nn2->power;
    int teor1 = sz1 + pow1;
    int teor2 = sz2 + pow2;
    if(teor1 != teor2) {
        return teor1 > teor2;
    }
    long* t1 = nn1->cont + teor1 - 1;
    long* t2 = nn2->cont + teor1 - 1;
    long* start = nn1->cont;
    while(t1 >= start) {
        if(*t1 != *t2) {
            return *t1 > *t2;
        }
        t1--;
        t2--;
    }
    return 0;
}

arr* fromnumeroN(arr* orig, int start, int len)
{
    if(len <= 0) { // causato dall'algoritmo, lunghezza negativa crea un numero ==0
        return zero();
    } else {
        arr* ret = allocarr();
        if(start == 0) { // prima parte sempre completa
            ret->cont = orig->cont;
            if(len >= orig->last) {
                // chiedo piu' di quel che c'e'
                ret->last = orig->last;
            } else {
                ret->last = len;
                if(iszero(ret)) {
                    libera(ret, 0);
                    return zero();
                }
            }
        } else {
            // seconda parte
            if(len >= orig->last) {
                // chiedo piu' di quel che c'e'
                libera(ret, 0);
                return zero();
            } else {
                ret->cont = orig->cont + len;
                ret->last = orig->last - len;
            }
        }

        ret->base = orig->base;
        ret->esp = orig->esp;
        ret->piccole = orig->piccole;
        ret->power = orig->power;

        ret->len = ret->last;
        assert(ret->last > 0);
        return ret;
    }
}

void reset(arr* curr)
{
    curr->power = 0;
    curr->last = 0;
    memset(curr->cont, 0, curr->len * sizeof(long));
}

void shift(arr* curr, int q) { curr->power += q; }

void filltolength(char* buf, char* buf1, int digits)
{
    int quanti = digits - strlen(buf);
    // se numero ha meno di DIGITS cifre, metti '0' iniziali sufficienti
    for(int i = 0; i < quanti; i++) {
        buf1[i] = '0';
    }
    if(quanti < 0) {
        printf("ERROR FILL %d %d %ld %s \n", digits, quanti, strlen(buf), buf);
    }
    strncpy(buf1 + quanti, buf, strlen(buf));
}

char* molti(char* s, int intf)
{
    char* ret = malloc(strlen(s) * intf + 1);
    char* q = ret;
    for(int i = 0; i < intf; i++) {
        char* ss = s;
        while(*ss != '\0') {
            *q++ = *ss++;
        }
        *q = '\0';
    }
    printf("number length: %ld\n", strlen(ret));
    return ret;
}

arr* split(arr* p)
{
    // RIFARE METTER VERSO in arra!!! se non non va! check se ultimo=0 non metto last deve essere giusto
    assert(p->base == 2 && p->esp % 2 == 0);
    int newespo = p->esp / 2;
    arr* ret = create(NULL, p->len * 2, p->power, p->base, newespo);
    long divisore = pow(2, newespo);
    ret->last = p->last * 2;
    for(int i = 0; i < p->last; i++) {
        long n = p->cont[i];
        long n1 = n >> newespo;
        long n2 = n % divisore;
        assert(n1 != 0 || n2 != 0);
        //  printf("split %ld %ld\n", n1, n2);
        if(ret->piccole) {

            ret->cont[i * 2] = n2;
            if(n1 != 0 || i < p->last - 1) {
                ret->cont[i * 2 + 1] = n1;
            } else {
                ret->last -= 1;
            }
        } else {
            if(n1 != 0 || i > 0) {
                ret->cont[i * 2] = n1;
            } else {
                ret->last -= 1;
            }
            ret->cont[i * 2 + 1] = n2;
        }
    }
    //  printf("finedisplit res=\n");
    return ret;
}

char* tostr(arr* p)
{
    arr* q = NULL;
    arr* q1 = NULL;
    if(p == NULL) {
        return "NULL";
    }
    if(iszero(p)) {
        return "0";
    }
    if(p->base != 10) {
        long massimo = pow(p->base, p->esp);
        if(massimo > pow(2, 30)) {
            printf("\t\tWARNING: POssible overflow converting %ld\n", massimo);
            if(p->base != 2) {
                printf("cant convert big number if base != 2\n");
                return NULL;
            }
            p = split(p);
            q = p;
            // spli se potenza =2 divido umero a meta'
        }
    }

    //     IN SOSPESO se usare digi oppure 9!!!!
    //     FORSE prima raddoppiare le cifre se maggiore di 2**30
    //     soezzandole ognuna in due!!!
    if(p->base != 10) {
        p = cambiabase(p, 10, DIGITS); // ricorda invert()!!
        q1 = p;
        //    dumpi(p);
    }
    int digi = p->base == 10 ? p->esp : digits(p->base, p->esp);
    int start = p->last - 1;
    for(; start >= 0 && p->cont[start] == 0; start--) {
        ;
    }

    char buf[digi + 1];
    char buf1[digi + 1];
    char* ret = malloc(digi * (p->len + p->power) + 50); // 1);
    char* cursor = ret;
    int i = 0;
    while(i <= start) {
        sprintf(buf, "%ld", p->cont[p->piccole == 1 ? start - i : i]);
        filltolength(buf, buf1, digi);
        //  printf("lenbuf %ld\n",strlen(buf1));
        strncpy(cursor, buf1, digi);
        cursor += digi;
        i++;
    }
    // rimepi con 10** DIGITS il fondo del numero se power >0
    for(int k = 0; k < p->power; k++) {
        for(int q = 0; q < digi; q++) {
            *cursor++ = '0';
        }
    }
    *cursor = '\0';
    while(*ret == '0') { // dlete leading zeros
        ret++;
    }
#if DEBUG == 1
    sprintf(cursor, " (l=%d,p=%d,b=%ld,e=%ld)", p->last, p->power, p->base, p->esp);
#endif
    if(q != NULL) {
        libera(q, 1);
    }
    if(q1 != NULL) {
        libera(q1, 1);
    }
    return ret;
}
