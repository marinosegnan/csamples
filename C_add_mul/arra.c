#include <arra.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static arr zero;
void initzero()
{
    zero.power = 0;
    zero.esp = DIGITS;
    zero.base = 10;
    zero.len = 1;
    zero.last = 1;
    zero.cont = malloc(1 * sizeof(long));
    long* dest = zero.cont;
    *dest = 0;
}
arr* iszero(arr* x, arr* y)
{
    return (x->last == 1 && *(x->cont) == 0) || (x->last == 1 && *(x->cont) == 0) ? &zero : NULL;
}

int positivo(arr* num) { return num->last > 0 && num->cont[0] != 0; }

long frombin(arr* num, int quanti)
{
    long fattore = pow(num->base, num->esp);
    long ret = 0;

    if(quanti > num->last) {
        quanti = num->last;
    }
    for(int i = 0; i < quanti; i++) {
        ret = ret * fattore + num->cont[i];
    }
    return ret;
}

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
    return tobase(numero, 2, bits);
}

void minidiv(long num, long divi,long* res){
    long v1 = num/divi;
    long t2 = v1 /divi;
    long v2=v1%divi;
    long v3 = num%divi;
 //   printf("%ld %ld %ld %ld\n", num,t2,v2,v3);
    *res++ = t2;
    *res++=v2;
    *res++=v3;
}

static long work[3];

arr* tobaseNONVA(arr* numero, int base, int digits)
{
    // da aggiustare le lugnhzze del rislutato
 /*   long* nuovo = malloc(numero->len * 4 * sizeof(long));
    numero->len *= 4;
    long* p = numero->cont;
    long* q = nuovo;
    while(q - nuovo < numero->last) {
        *q++ = *p++;
    }
    while(q - nuovo < numero->len) {
        *q++ = 0;
    }
    free(numero->cont);
    numero->cont = nuovo;
*/
    invert(numero);
    long divisore = pow(base, digits);
    int l2 = 2;
    long fattore = pow(numero->base, numero->esp);
    arr* parziale = create(NULL, numero->len , 0, 10, 9);
    int crea = 1;
    arr* ret = create(NULL, numero->len , 0, base, digits);
    arr*orig = numero;
    long* retpt = ret->cont;
    int giro =0;
    printf("dumpi tobase input\n");
    dumpi(numero);
    while(positivo(orig)) {
        long* l1 = orig->cont + orig->last;
        long dividendo = frombin(orig, l2);
        long* p = parziale->cont;
        for(long* pos = orig->cont + l2; pos < l1; pos++) {
            // printf("D %ld\n", p- parziale->cont);
            if( dividendo >= divisore * divisore) {
               minidiv(dividendo,divisore,work);
               *p++ = work[0];
               *p++ = work[1];
                dividendo = work[2];
            } else if(dividendo >= divisore) {

                *p++ = dividendo / divisore;
                dividendo = dividendo % divisore;
            } else {
                if(parziale->last > 0) { // solo zeri significativi
                    *p++ = 0;
                }
            }
            long oldiv = dividendo;
        dividendo = dividendo * fattore + *pos;
            if(dividendo >= divisore * divisore) {
         //       printf("old, att %ld %ld %ld %ld %ld,\n", oldiv, fattore, *pos, dividendo,l1-pos);
            }
        
        }
        if(dividendo >= divisore) {
            *p++ = dividendo / divisore;
            dividendo = dividendo % divisore;
        } else {
            *p++ = 0;
        }
        // inverti i due contenitori
      
        parziale->last = p - parziale->cont;
          printf("dumpi tobase parziale : %ld\n",dividendo);
    dumpi(parziale);
    if (crea == 1){
        crea =0;
         orig = parziale;
           parziale = create(NULL, numero->len , 0, 10, 9);
    } else {
         arr* temp = orig;
        orig = parziale;
        parziale = temp;
        parziale->last = 0;
    }
       
        *retpt++ = dividendo; // ret->cont[ret->last] = dividendo;
        ret->last++;
           printf("dumpi risultato\n");
    dumpi(ret);
        if (giro ==0){
  //         printf("tobase %s %s %ld\n",tostr(numero),tostr(parziale),divisore);
        }
        giro++;
    }
    return ret;
}


arr* tobase(arr* numero, int base, int digits)
{
    // da aggiustare le lugnhzze del rislutato
    long* nuovo = malloc(numero->len * 2 * sizeof(long));
    numero->len *= 2;
    long* p = numero->cont;
    long* q = nuovo;
    while(q - nuovo < numero->last) {
        *q++ = *p++;
    }
    while(q - nuovo < numero->len) {
        *q++ = 0;
    }
    free(numero->cont);
    numero->cont = nuovo;

    invert(numero);
    long divisore = pow(base, digits);
    int l2 = 2;
    long fattore = pow(numero->base, numero->esp);
    arr* parziale = create(NULL, numero->len * 2, 0, numero->base, numero->esp);
    arr* ret = create(NULL, numero->len * 2, 0, base, digits);
    long* retpt = ret->cont;
    while(positivo(numero)) {
        long* l1 = numero->cont + numero->last;
        long dividendo = frombin(numero, l2);
        long* p = parziale->cont;
        for(long* pos = numero->cont + l2; pos < l1; pos++) {
            // printf("D %ld\n", p- parziale->cont);
            if(0 && dividendo >= divisore * divisore) {
                long q = dividendo / divisore;
                *p++ = q / divisore;
                *p++ = q % divisore;
                dividendo = dividendo % divisore;
            } else if(dividendo >= divisore) {

                *p++ = dividendo / divisore;
                dividendo = dividendo % divisore;
            } else {
                if(parziale->last > 0) { // solo zeri significativi
                    *p++ = 0;
                }
            }
            long oldiv = dividendo;
            dividendo = dividendo * fattore + *pos;
            if(dividendo >= divisore * divisore) {
                printf("old, att %ld %ld %ld %ld,\n", oldiv, fattore, *pos, dividendo);
            }
        }
        if(dividendo >= divisore) {
            *p++ = dividendo / divisore;
            dividendo = dividendo % divisore;
        } else {
            *p++ = 0;
        }
        // inverti i due contenitori
        parziale->last = p - parziale->cont;
        arr* temp = numero;
        numero = parziale;
        parziale = temp;
        parziale->last = 0;
        *retpt++ = dividendo; // ret->cont[ret->last] = dividendo;
        ret->last++;
    }
    return ret;
}

void dumpi(arr* num)
{
    for(int i = 0; i < num->last; i++) {
        printf("%ld\n", num->cont[i]);
    }
}
arr* create(char* n, int sz, int pow, int base, int esp)
{
    arr* ret = malloc(sizeof(arr));
    ret->power = pow;
    ret->esp = esp;
    ret->base = base;

    if(n != NULL) {
        int quante = strlen(n) / esp;
        int resto = strlen(n) % esp;
        if(resto > 0) {
            quante++;
            resto = esp - resto;
        }
        char nome[quante * esp + 1];
        // riempi a giusta quantita per avre un multiplo
        for(int i = 0; i < resto; i++) {
            nome[i] = ' ';
        }
        strncpy(nome + resto, n, strlen(n));
        nome[quante * esp] = '\0';
        ret->len = quante;

        ret->last = ret->len;
        ret->cont = malloc(ret->len * sizeof(long));

        // crea capovolto, cosi' indici piu' leggibili partendo da 0
        char buf[esp + 1];
        int quanti = strlen(nome);
        char* p = nome + quanti;
        for(int i = 0; i < quante; i++) {
            strncpy(buf, p - (esp * (i + 1)), esp);
            buf[esp] = '\0';
            ret->cont[i] = atol(buf);
        }
    } else {

        ret->len = sz;
        ret->last = 0;
        ret->cont = malloc(ret->len * sizeof(long));
        long* q = ret->cont + sz;
        while(--q >= ret->cont) {
            *q = 0;
        }
    }
    //   printf("CREO %s\n",tostr(ret,0));

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
    return num;
}

int greater(arr* nn1, arr* nn2)
{
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
    // printf("fromnumero %s %d %d\n",tostr(orig),start,len);
    arr* ret = malloc(sizeof(arr));

    ret->esp = orig->esp;
    if(len <= 0) { // causato dall'algoritmo, lunghezza negativa crea un numero ==0
        return &zero;
    } else {
        if(start == 0 && len > orig->len) {
            len = orig->len;
        }

        ret->power = orig->power;
        ret->len = len;
        ret->last = len;
        ret->cont = orig->cont + start; // non creare nulla
    }

    //  printf("CREO %s\n",tostr(ret));

    return ret;
}

void reset(arr* curr)
{
    curr->power = 0;
    curr->last = 0;
    long* p = curr->cont;
    long* end = curr->cont + curr->len;
    while(p < end) {
        *p++ = 0;
    }
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

char* tostr(arr* p)
{
    if(p == NULL) {
        return "NULL";
    }
    int start = p->last - 1; // p->len -1;
    for(; start >= 0 && p->cont[start] == 0; start--) {
        ;
    }
    char buf[p->esp + 1];
    char buf1[p->esp + 1];
    char* ret = malloc(p->esp * (p->len + p->power) + 10); // 1);
    char* cursor = ret;
    int i = 0;
    while(i <= start) {
        sprintf(buf, "%ld", p->cont[start - i]);
        filltolength(buf, buf1, p->esp);
        //  printf("lenbuf %ld\n",strlen(buf1));
        strncpy(cursor, buf1, p->esp);
        cursor += p->esp;
        i++;
    }
    // rimepi con 10** DIGITS il fondo del numero se power >0
    for(int k = 0; k < p->power; k++) {
        for(int q = 0; q < p->esp; q++) {
            *cursor++ = '0';
        }
    }
    *cursor = '\0';
    while(*ret == '0') { // dlete leading zeros
        ret++;
    }
    sprintf(cursor, " (%d,%d)", p->last, p->power);
    return ret;
}
