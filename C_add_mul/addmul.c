#include <addmul.h>
#include <assert.h>
#include <debug.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tempi.h>

void sumsimple(arr* nn1, arr* nn2)
{
    // copiata da quella che crea la copia
    int sz1 = nn1->last;
    int sz2 = nn2->last;
    int pow1 = nn1->power;
    int pow2 = nn2->power;
    int diffpow = DIF(pow1, pow2); // pow1 > pow2 ? pow1 - pow2 : pow2 - pow1;
    int teor1 = sz1 + pow1;
    int teor2 = sz2 + pow2;
    int finalsize = MAX(teor1, teor2) + 1;
    int difflen = DIF(teor1, teor2);

    int required = finalsize - diffpow;
    if(0 && required > nn1->len) {
        //  printf("RIALLOCO %d %d\n",required,nn1->len);
        // fai piu' spazio
        required += 5;
        long* nuovo = malloc(required * sizeof(long));
        nn1->len = required;
        long* p = nn1->cont;
        long* q = nuovo;
        while(q - nuovo < nn1->last) {
            *q++ = *p++;
        }
        while(q - nuovo < nn1->len) {
            *q++ = 0;
        }
        free(nn1->cont);
        nn1->cont = nuovo;
    }
    assert(required <= nn1->len);
#if DEBUG == 1
    printf("sum input: %s %s\n", tostr(nn1), tostr(nn2));
#endif

    //  arr *ret = create(NULL, finalsize, MIN(nn1->power, nn2->power),
    //                  10,DIGITS); // nn1->digits);
    long* attuale = nn1->cont;
    long* p1 = nn1->cont;
    long* p2 = nn2->cont;
    long fattore = pow(10, DIGITS); // nn1->digits);
    long riporto = 0;
    long* endloop = 0;
    if(pow1 < pow2) {
        attuale += diffpow;
        p1 += diffpow;
    } else if(pow1 > pow2) {
        endloop = attuale + diffpow;
        while(attuale < endloop) {
            *attuale++ = *p2++;
        }
    }
    endloop = nn1->cont + MIN(teor1, teor2); // fine parte coumne
    while(attuale < endloop) {
        long v1 = *p1++;
        long v2 = *p2++;
        long val = v1 + v2 + riporto;
        *attuale++ = val % fattore;
        riporto = val / fattore;
    }
    if(teor2 > teor1) {
        // coda op2
        endloop = attuale + difflen;
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
    while(attuale > nn1->cont && *--attuale == 0) {
        ;
    }
    nn1->last = attuale - nn1->cont + 1;
    assert(nn1->last > 0);
#if DEBUG == 1
    printf("sum res: %s\n", tostr(nn1));
#endif
}

void sumsimpleCORRENTETENERE(arr* nn1, arr* nn2)
{
    // versione che usa il primo operando per contenere il rsultato

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
    printf("sum input: %s %s\n", tostr(nn1), tostr(nn2));
#endif
    long* attuale = nn1->cont;
    long* base = attuale;

    long* p1 = nn1->cont;
    long* p2 = nn2->cont;
    long fattore = pow(10, DIGITS); // nn1->digits);

    long riporto = 0;
    long* endloop = 0;

    if(pow1 < pow2) {
        attuale += diffpow;
        p1 += diffpow;
        // printf("DIFF %d\n",diffpow);
        /* NON SERVE!
         endloop = attuale + diffpow;
        while (attuale < endloop) {
          *attuale++ = *p1++;
        }*/
    } else if(pow1 > pow2) {
        endloop = attuale + diffpow;
        while(attuale < endloop) {
            *attuale++ = *p2++;
        }
    }

    int lastcomuni = MIN(teor1, teor2);
    endloop = base + lastcomuni;
    while(attuale < endloop) {
        long v1 = *p1++;
        long v2 = *p2++;
        long val = v1 + v2 + riporto;
        *attuale++ = val % fattore;
        riporto = val / fattore;
    }

    if(teor1 > teor2) {
        // coda op1
        endloop = base + teor1;
        while(attuale < endloop) {
            long v1 = *p1++;
            long val = v1 + riporto;
            *attuale = val % fattore;
            riporto = val / fattore;
            if(riporto == 0) {
                break;
            }
        }
    } else if(teor2 > teor1) {
        // coda op2

        endloop = base + teor2;
        while(attuale < endloop) {
            if(p2 - nn2->cont == nn2->last) {
                printf("ciao %ld %ld %ld\n", base - nn1->cont, attuale - nn1->cont, endloop - attuale);
            }
            long v1 = *p2++;
            long val = v1 + riporto;
            *attuale++ = val % fattore;
            riporto = val / fattore;
            if(riporto == 0) {
                break;
            }
        }
    }
    if(riporto != 0) {
        // int ma = sz1 > sz2 ? sz1 : sz2;
        *attuale = riporto;
        nn1->last = finalsize + 1;
    } else {
        nn1->last = finalsize;
    }
    while(attuale > nn1->cont && *--attuale == 0) {
#if DEBUG == 3
        printf("riduco %s\n", tostr(nn1));
#endif
        ;
    }
    nn1->last = attuale - nn1->cont + 1;
    if(nn1->last == 0) {
        nn1->last = 1;
    }
#if DEBUG == 1
    printf("sum res: %s\n", tostr(nn1));
#endif
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
    int difflen = DIF(teor1, teor2);
#if DEBUG == 1
    printf("sum input: %s %s\n", tostr(nn1), tostr(nn2));
#endif

    arr* ret = create(NULL, finalsize, MIN(nn1->power, nn2->power), 10, DIGITS); // nn1->digits);
    long* attuale = ret->cont;
    long* p1 = nn1->cont;
    long* p2 = nn2->cont;
    long fattore = pow(10, DIGITS); // nn1->digits);
    long riporto = 0;
    long* endloop = 0;
    // in caso di differenza di potenze,
    // gli 0 non vengono coipiati perche' l'array e' azzerato alla creazione
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
    endloop = ret->cont + MIN(teor1, teor2); // fine parte coumne
    while(attuale < endloop) {
        long v1 = *p1++;
        long v2 = *p2++;
        long val = v1 + v2 + riporto;
        *attuale++ = val % fattore;
        riporto = val / fattore;
    }

    if(teor1 > teor2) {
        // coda op1
        endloop = attuale + difflen;
        while(attuale < endloop) {
            long v1 = *p1++;
            long val = v1 + riporto;
            *attuale++ = val % fattore;
            riporto = val / fattore;
        }
    } else if(teor2 > teor1) {
        // coda op2
        endloop = attuale + difflen;
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
#if DEBUG == 1
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

    ret->last = finalsize;
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
    long fattore = pow(10, DIGITS); // nn1->digits);
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
            *ir = riporto;
        }
        temp->last = ir - parziale + 1;
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
    long fattore = pow(10, DIGITS);      // nn1->digits);
    long fattore2 = pow(10, DIGITS * 2); // nn1->digits * 2);
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
arr* karat(arr* x, arr* y)
{
#if DEBUG == 2
    printf("KARAT %s %s\n", tostr(x), tostr(y));
#endif
    if(x->last <= 1 || y->last <= 1) {
#if DEBUG == 1
        printf("foglia %s  %s\n", tostr(x), tostr(y));
#endif
        arr* poi = iszero(x, y);
        if(poi != NULL) {
            return poi;
        }
        arr* re = mul(x, y);
        //    printf("ret semplice %s %s %s\n",tostr(x),tostr(y),tostr(re));
        return re;
    } else {
        //    print('normale')
        long m = MAX(x->last, y->last);
        long m2 = m / 2;
        arr* b = fromnumeroN(x, 0, m2);
        arr* a = fromnumeroN(x, m2, x->last - m2);
        arr* c = fromnumeroN(y, m2, y->last - m2);
        arr* d = fromnumeroN(y, 0, m2);
#if DEBUG == 2
        printf("abcd %s %s %s %s\n", tostr(a), tostr(b), tostr(c), tostr(d));
#endif
        arr* z0 = karat(b, d);
        arr* p1 = sumsimpleC(a, b);
        arr* p2 = sumsimpleC(c, d);
#if DEBUG == 1
        printf("p1 p2 %s %s\n", tostr(p1), tostr(p2));
#endif
        arr* z1 = karat(p1, p2);
#if DEBUG == 1
        printf("ULT z1 %s \n", tostr(z1));
#endif
        arr* z2 = karat(a, c);
#if DEBUG == 1
        printf("z012 %s %s %s \n", tostr(z0), tostr(z1), tostr(z2));
#endif

        //  return (z2 * pot1) + ((z1 - z2 - z0) * pot) + (z0)
        arr* a1 = sumsimpleC(z2, z0);
        //  print('z1,a1',z1,a1)
        arr* a2 = difsimpleC(z1, a1);
        //  print('subito dopo a2', a2)
        a2->power += m2;
        //   print('espoprima',z2.esp)
        z2->power += m2 * 2;
#if DEBUG == 1
        printf("z2 a2 %s %s\n", tostr(z2), tostr(a2));
#endif
        arr* a3 = sumsimpleC(z2, a2);
#if DEBUG == 1
        printf("a3 %s\n", tostr(a3));
#endif
        arr* a4 = sumsimpleC(a3, z0);
#if DEBUG == 2
        printf("a1234: %s %s %s %s\n", tostr(a1), tostr(a2), tostr(a3), tostr(a4));
#endif
        return a4;
    }
}
