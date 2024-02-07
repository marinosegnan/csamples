#include <assert.h>
#include <debug.h>
#include <includere.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <tempi.h>

arr* sumsimple(arr* nn1, arr* nn2)
{
    // versione che NON  crea una copia per il risultato

    // se due numeri sono sfasati,cioe' uno contiene 0 iniziali,
    // l'altro viene copiato direttamente per tutto il primo tratto
    // vi e' poi una parte comune
    // a seguire una coda dove si somma il piu' lungo col riporto
    //   es 56783300000 + 45678944444645
    // calcola spazio finale + 1
#if DEBUG == 5
    printf("sum input: %s  ---------------- %s\n", tostr(nn1), tostr(nn2));
#endif
    // scambia eventualmente nn1 con nn2, il primo sara' il rislutato
    // il risultato sara' quello che ha la potenza minore
    // che sara' quello da cui si inizia a copiare
    if(nn1->power > nn2->power) {
        arr* tmp = nn1;
        nn1 = nn2;
        nn2 = tmp;
    }
    arr* ret = nn1;
    int sz1 = nn1->last;
    int sz2 = nn2->last;
    int pow1 = nn1->power;
    int pow2 = nn2->power;
    int diffpow = DIF(pow1, pow2); // pow1 > pow2 ? pow1 - pow2 : pow2 - pow1;
    int teor1 = sz1 + pow1;
    int teor2 = sz2 + pow2;
    int finalsize = MAX(teor1, teor2) + 1; // per sicurezza finalsize e' piu' grande per tenerrw onto di tutti
    // i casi possibili;  1 per il riporto eventule
    if(finalsize > ret->len) {
        //  printf("RIALLOCO %d %d\n",finalsize,nn1->len);
        // fai piu' spazio
        sistema(ret, finalsize);
    }
    long* attuale = ret->cont;
    long* p1 = nn1->cont;
    long* p2 = nn2->cont;
#if VERSIONE == 0
    long fattore = divisore(ret); // nn1->digits);
#endif
#if VERSIONE == 1
    long fattore = POTENZA10; // digits(ret->base,ret->esp));
#endif
#if VERSIONE == 2
    long fattore = POTENZA2; // digits(ret->base,ret->esp));
#endif
    long riporto = 0;
    long* endloop = 0;
    int intersez = MIN(teor1, teor2) - MAX(pow1, pow2);
    if(intersez < 0) {
        intersez = 0;
    }
#if DEBUG == 4
    printf("sum intersez %d\n", intersez);
#endif
    if(pow1 < pow2) {
        attuale += MIN(diffpow, sz1);
        p1 += MIN(diffpow, sz1);
        //   while(attuale < endloop) {
        //       *attuale++ = *p1++;
        //   }
        if(diffpow > sz1) {
            // riempi con zeri
            endloop = attuale + diffpow - sz1;
            while(attuale < endloop) {
                *attuale++ = 0;
            }
        }
    }
    /* non si verifica, pow1 sempre <= pow2 a questo punto
     * else if(pow1 > pow2) {
            endloop = attuale + MIN(diffpow, sz2);
            while(attuale < endloop) {
                *attuale++ = *p2++;
            }
            if(diffpow > sz2) {
                endloop = attuale + diffpow -sz2;
                while(attuale < endloop) {
                    *attuale++ = 0;
                }
            }
        }*/
    endloop = attuale + intersez;
    while(attuale < endloop) {
        long v1 = *p1++;
        long v2 = *p2++;
        long val = v1 + v2 + riporto;
        *attuale++ = val % fattore;
        riporto = val / fattore;
    }
    if(teor1 > teor2) { // la coda e' gi' nel risultato
        // coda op1
        if(riporto != 0) {
            *attuale = riporto;
        }
        attuale += sz1 - (p1 - nn1->cont);
        p1 += sz1 - (p1 - nn1->cont);
        /*  endloop = attuale + sz1 - (p1 - nn1->cont);
          while(attuale < endloop) {
              long v1 = *p1++;
              long val = v1 + riporto;
              *attuale++ = val % fattore;
              riporto = val / fattore;
          }*/
    } else if(teor2 > teor1) {
        // coda op2
        endloop = attuale + sz2 - (p2 - nn2->cont);
        while(attuale < endloop) {
            long v1 = *p2++;
            long val = v1 + riporto;
            *attuale++ = val % fattore;
            riporto = val / fattore;
        }
    }
    if(riporto != 0) {
        *attuale++ = riporto;
    }
    while(attuale > ret->cont && *--attuale == 0) {
        ;
    }
    ret->last = attuale - ret->cont + 1;
    assert(ret->last > 0);
#if DEBUG == 5
    printf("sum res: %s\n", tostr(ret));
#endif
    return ret;
}

arr* sumsimpleC(arr* nn1, arr* nn2)
{
    // versione che crea una copia per il risultato

    // se due numeri sono sfasati,cioe' uno contiene 0 iniziali,
    // l'altro viene copiato direttamente per tutto il primo tratto
    // vi e' poi una parte comune
    // a seguire una coda dove si somma il piu' lungo col riporto
    //   es 56783300000 + 45678944444645
    // calcola spazio finale + 1

    int sz1 = nn1->last;
    int sz2 = nn2->last;
    int pow1 = nn1->power;
    int pow2 = nn2->power;
    int diffpow = DIF(pow1, pow2); // pow1 > pow2 ? pow1 - pow2 : pow2 - pow1;
    int teor1 = sz1 + pow1;
    int teor2 = sz2 + pow2;
    int finalsize = MAX(teor1, teor2) + 1;
#if DEBUG == 5
    printf("sum input: %s  ---------------- %s\n", tostr(nn1), tostr(nn2));
#endif

    arr* ret = create(NULL, finalsize, MIN(pow1, pow2), 10, DIGITS); // nn1->digits);
    long* attuale = ret->cont;
    long* p1 = nn1->cont;
    long* p2 = nn2->cont;
#if VERSIONE == 0
    long fattore = divisore(ret); // nn1->digits);
#endif
#if VERSIONE == 1
    long fattore = POTENZA10; // digits(ret->base,ret->esp));
#endif
#if VERSIONE == 2
    long fattore = POTENZA2; // digits(ret->base,ret->esp));
#endif
    long riporto = 0;
    long* endloop = 0;

    // in caso di differenza di potenze,
    // gli 0 non vengono coipiati perche' l'array e' azzerato alla creazione
    int intersez = MIN(teor1, teor2) - MAX(pow1, pow2);
    if(intersez < 0) {
        intersez = 0;
    }
#if DEBUG == 4
    printf("sum intersez %d\n", intersez);
#endif
    if(pow1 < pow2) {
        endloop = attuale + MIN(diffpow, sz1);
        while(attuale < endloop) {
            *attuale++ = *p1++;
        }
        if(diffpow > sz1) {
            attuale += diffpow - sz1;
            /*  il risultto e' stato azzerato alla creazione
             endloop = attuale + diffpow - sz1;
             while(attuale < endloop) {
                 *attuale++ = 0;
             }
              * */
        }

    } else if(pow1 > pow2) {
        endloop = attuale + MIN(diffpow, sz2);
        while(attuale < endloop) {
            *attuale++ = *p2++;
        }
        if(diffpow > sz2) {
            attuale += diffpow - sz2;
            /*  il risultto e' stato azzerato alla creazione
                     endloop = attuale + diffpow -sz2;
                while(attuale < endloop) {
                    *attuale++ = 0;
                }*/
        }
    }
    endloop = attuale + intersez;
    while(attuale < endloop) {
        long v1 = *p1++;
        long v2 = *p2++;
        long val = v1 + v2 + riporto;
        *attuale++ = val % fattore;
        riporto = val / fattore;
    }

    if(teor1 > teor2) {
        // coda op1
        endloop = attuale + sz1 - (p1 - nn1->cont);
        while(attuale < endloop) {
            long v1 = *p1++;
            long val = v1 + riporto;
            *attuale++ = val % fattore;
            riporto = val / fattore;
        }
    } else if(teor2 > teor1) {
        // coda op2
        endloop = attuale + sz2 - (p2 - nn2->cont);
        while(attuale < endloop) {
            long v1 = *p2++;
            long val = v1 + riporto;
            *attuale++ = val % fattore;
            riporto = val / fattore;
        }
    }
    if(riporto != 0) {
        *attuale++ = riporto;
    }
    while(attuale > ret->cont && *--attuale == 0) {
        ;
    }
    ret->last = attuale - ret->cont + 1;
    assert(ret->last > 0);
#if DEBUG == 5
    printf("sum res: %s\n", tostr(ret));
#endif
    return ret;
}

arr* difsimpleC(arr* nn1, arr* nn2)
{
    // se due numeri sono sfasati,cioe' uno contiene 0 iniziali,
    // l'altro viene copiato direttamente per tutto il primo tratto
    // vi e' poi una parte comune
    // a seguire una coda dove si somma il piu' lungo col riporto
    //   es 56783300000 + 45678944444645
    // calcola spazio finale + 1

    int sz1 = nn1->last;
    int sz2 = nn2->last;
    int pow1 = nn1->power;
    int pow2 = nn2->power;
    int diffpow = pow1 > pow2 ? pow1 - pow2 : pow2 - pow1;
    int teor1 = sz1 + pow1;
    int teor2 = sz2 + pow2;

    int finalsize = teor1 > teor2 ? teor1 : teor2;
#if DEBUG == 1
    printf("dif input: %s %s\n", tostr(nn1), tostr(nn2));
#endif
    arr* ret = create(NULL, finalsize + 1, MIN(nn1->power, nn2->power), 10, DIGITS); // nn1->digits);
    long* attuale = ret->cont;
    long* base = attuale;

    long* p1;
    long* p2;
    if(greater(nn1, nn2)) {
        p1 = nn1->cont;
        p2 = nn2->cont;
    } else {
        p2 = nn1->cont;
        p1 = nn2->cont;
    }
    long fattore = pow(10, DIGITS); // nn1->digits);

    long prestito = 0;
    long* endloop = 0;
    if(pow1 < pow2) {
        endloop = attuale + diffpow;
        while(attuale < endloop) {
            *attuale++ = *p1++;
        }
    } else if(pow1 > pow2) {
        endloop = attuale + diffpow;
        while(attuale < endloop) {
            *attuale++ = *p2++;
        }
    }
    int lastcomuni = MIN(teor1, teor2);
    endloop = base + lastcomuni;
    while(attuale < endloop) {
        long v1 = *p1++ - prestito;
        long v2 = *p2++;
        if(v1 >= v2) {
            long val = v1 - v2;
            *attuale++ = val;
            prestito = 0;
        } else {
            long val = v1 + fattore - v2;
            *attuale++ = val;
            prestito = 1;
        }
    }
    if(teor1 > teor2) {
        // coda op1
        endloop = base + teor1;
        while(attuale < endloop) {
            long v1 = *p1++;
            if(prestito == 1) {
                if(v1 == 0) {
                    v1 = fattore - 1;
                } else {
                    v1--;
                    prestito = 0;
                }
            }
            *attuale++ = v1;
        }
    } else if(teor2 > teor1) {
        // coda op2
        endloop = base + teor2;
        while(attuale < endloop) {
            long v1 = *p2++;
            if(prestito == 1) {
                if(v1 == 0) {
                    v1 = fattore - 1;
                } else {
                    v1--;
                    prestito = 0;
                }
            }
            *attuale++ = v1;
        }
    }
    attuale--;
    while(*attuale == 0 && attuale > ret->cont) {
        attuale--;
    }
    ret->last = 1 + attuale - ret->cont;
#if DEBUG == 1

    printf("dif output: %s\n", tostr(ret));
#endif
    return ret;
}

arr* mul(arr* nn1, arr* nn2)
{
    long* n1 = nn1->cont;
    long* n2 = nn2->cont;
    int l1 = nn1->last;
    int l2 = nn2->last;
#if VERSIONE == 0
    long fattore = divisore(nn1); // nn1->digits);
#endif
#if VERSIONE == 1
    long fattore = POTENZA10; // digits(ret->base,ret->esp));
#endif
#if VERSIONE == 2
    long fattore = POTENZA2; // digits(ret->base,ret->esp));
#endif
    arr* totale = NULL;
    arr* temp = create(NULL, l1 + l2, 0, 10, DIGITS); // nn1->digits);
    long* parziale = temp->cont;
    long* lim1 = n1 + l1;
    long* lim2 = n2 + l2;
    // printf("Mulast %s %s\n",tostr(nn1),tostr(nn2));
    for(long* ip = n1; ip < lim1; ip++) {
        long riporto = 0;
        long* ir = parziale;
        for(long* iq = n2; iq < lim2; iq++) {
            long p = *ip * (*iq) + riporto;
            *ir++ = p % fattore;
            riporto = p / fattore;
        }
        if(riporto > 0) {
            *ir++ = riporto;
        }
        temp->last = ir - parziale;
        //  printf("mulast %s\n",tostr(temp));
        if(totale == NULL) {
            //   crea copia di lavoro al primo giro
            totale = temp;
            temp = create(NULL, l1 + l2, 0, 10, DIGITS); // nn1->digits);
            parziale = temp->cont;
        } else {
            shift(temp, ip - n1); // aumenta la potenza (sposat a sinistra)
            sumsimple(totale, temp);
            reset(temp);
        }
        //  printf("Mulastparziale %s\n",tostr(totale));
    }
    libera(temp, 1);
    return totale;
}

arr* mul3(arr* nn1, arr* nn2)
{

    // INCREDIBVILE A DIRSI:
    // sostituire DIGITS a nn1->digits moltiplica di parecchie volte la
    // velocita!!!!!

    // a ogni giro, prendo due coppie di cifre piccole,
    // ne vreo una grande come quando moltiplico in colonna, e conservo il
    // riporto. in questo modo riduco le copie e creo un numero di lavoro con la
    // meta' delle cifre.
#if VERSIONE == 0
    long fattore = divisore(nn1);
    long fattore2 = fattore * fattore;
#endif
#if VERSIONE == 1
    long fattore = POTENZA10; // digits(ret->base,ret->esp));
    long fattore2 = POTENZA1010;
#endif
#if VERSIONE == 2
    long fattore = POTENZA2; // digits(ret->base,ret->esp));
    long fattore2 = POTENZA22;
#endif
    long* n1 = nn1->cont;
    long* n2 = nn2->cont;
    long l1 = nn1->last;
    long l2 = nn2->last;
    long* lim1 = n1 + l1;
    long* lim2 = n2 + l2;
    arr* totale = create(NULL, l1 + l2, 0, 10, DIGITS * 2); // nn1->digits * 2);
    long* parziale = totale->cont;
    int count = 0; // cifre grandi
    for(long* ip1 = n1; ip1 < lim1; ip1 += 2, count++) {
        long riporto = 0;
        long* ir = parziale + count;
        long j1 = *ip1;
        long j2 = ip1 >= lim1 - 1 ? 0 : *(ip1 + 1); // dispari
        for(long* iq1 = n2; iq1 < lim2; iq1 += 2) {
            long k1 = *iq1;
            long k2 = iq1 >= lim2 - 1 ? 0 : *(iq1 + 1); // dispari
            long c1 = j1 * k1;
            long c2 = j2 * k1 + j1 * k2;
            long c3 = j2 * k2;
            long f6 = c2 % fattore;
            long f7 = c2 / fattore;
            long p = c1 + f6 * fattore + riporto + *ir;
            *ir++ = p % fattore2;
            riporto = p / fattore2 + c3 + f7;
        }
        if(riporto > 0) {
            *ir++ += riporto;
        }
        totale->last = ir - parziale;
    }
    return totale;
}

int piccolo(arr* x, arr* y)
{
    long* p1 = x->cont + x->last - 1;
    while(p1 > x->cont && *p1 == 0) {
        p1--;
    }
    long* p2 = y->cont + y->last - 1;
    while(p2 > y->cont && *p2 == 0) {
        p2--;
    }
    assert(p1 >= x->cont && p2 >= y->cont);
    return p1 == x->cont || p2 == y->cont;
}

arr* karat(arr* x, arr* y)
{
#if DEBUG == 4
    printf("KARAT %s %s\n", tostr(x), tostr(y));
#endif
    if(iszero(x) || iszero(y)) {
        return zero();
    }
    if(piccolo(x, y)) {
        return mul(x, y);
    }
    long m = MAX(x->last, y->last);
    long m2 = m / 2;
    arr* a = fromnumeroN(x, 1, m2);
    arr* b = fromnumeroN(x, 0, m2);
    arr* c = fromnumeroN(y, 1, m2);
    arr* d = fromnumeroN(y, 0, m2);
    arr* ac = karat(a, c);
    arr* bd = karat(b, d);
    arr* p1 = sumsimpleC(a, b);
    arr* p2 = sumsimpleC(c, d);
    arr* k3 = karat(p1, p2);
    arr* a1 = sumsimpleC(ac, bd);
    arr* abcd = difsimpleC(k3, a1);
    abcd->power += m2;
    ac->power += m2 * 2;
    arr* a3 = sumsimpleC(abcd, ac);
    arr* a4 = sumsimpleC(a3, bd);

    libera(a, 0);
    libera(b, 0);
    libera(c, 0);
    libera(d, 0);
    libera(a3, 1);
    libera(ac, 1);
    libera(abcd, 1);
    libera(k3, 1);
    libera(a1, 1);
    libera(bd, 1);
    libera(p1, 1);
    libera(p2, 1);
#if DEBUG == 4
    printf("kar res: %s\n", tostr(a4));
#endif
    return a4;
}
