#include <includere.h>
#include <assert.h>
#include <debug.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tempi.h>

/*  versione per numeri in base 2**30; us shift per moltiplicre.
 * c'e' anch ela versione di mul che genera numeri nel prodotto di 2*60 cifre
 * prtendo da 2 cifre 2**30; e' veloce m ovviamente non si puo'usare piu' di una volta;
 * tuttvia basterebbe splittare il numero spezzando ognuno in due cifre di nuovo
 * per ritornare ala partenza
*/

void sumbase2(arr* nn1, arr* nn2)
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
    // printf("sum input: %s %s\n",tostr(nn1),tostr(nn2));
    // arr *ret = create(NULL, finalsize+1, 0, nn1->digits);
    long* attuale = nn1->cont;
    long* base = attuale;

    long* p1 = nn1->cont;
    long* p2 = nn2->cont;
    long fattore = POTENZA2;

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
        riporto = val >> 30;/// fattore;
    }
    if(teor1 > teor2) {
        // coda op1
        endloop = base + teor1;
        while(attuale < endloop) {
            long v1 = *p1++;
            long val = v1 + riporto;
            *attuale = val % fattore;
            riporto = val >>30;/// fattore;
            if(riporto == 0) {
                break;
            }
        }
    } else if(teor2 > teor1) {
        // coda op2
        endloop = base + teor2;
        while(attuale < endloop) {
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
        *attuale++ = riporto;
        nn1->last = finalsize + 1;
    } else {
        nn1->last = finalsize;
    }
    while(attuale > nn1->cont && *--attuale == 0) {
        ;
    }
    nn1->last = attuale - nn1->cont + 1;
}

arr* muladdbase2(arr* nn1, arr* nn2)
{
    long* n1 = nn1->cont;
    long* n2 = nn2->cont;
    int l1 = nn1->last;
    int l2 = nn2->last;
    long fattore = POTENZA2;
    arr* totale = NULL;
    arr* temp = create(NULL, l1 + l2, 0, 2, 30); // nn1->digits);
    long* parziale = temp->cont;
    long* lim1 = n1 + l1;
    long* lim2 = n2 + l2;
    // printf("Mulast %s %s\n",tostr(nn1),tostr(nn2));
    for(long* ip = n1; ip < lim1; ip++) {
        long riporto = 0;
        long* ir = parziale;
        for(long* iq = n2; iq < lim2; iq++) {
            long p = *ip * (*iq) + riporto;
            *ir++ = (fattore - 1) & p;
            riporto = p >> 30;
        }
        if(riporto > 0) {
            *ir = riporto;
        }
        temp->last = ir - parziale + 1;
        //  printf("mulast %s\n",tostr(temp));
        if(totale == NULL) {
            //   crea copia di lavoro al primo giro
            totale = temp;
            temp = create(NULL, l1 + l2, 0, 2, 30); // nn1->digits);
            parziale = temp->cont;
        } else {
            shift(temp, ip - n1); // aumenta la potenza (sposat a sinistra)
            sumbase2(totale, temp);
            reset(temp);
        }
        //  printf("Mulastparziale %s\n",tostr(totale));
    }
    return totale;
}

arr* mulbase2(arr* nn1, arr* nn2)
{

    // INCREDIBVILE A DIRSI:
    // sostituire DIGITS a nn1->digits moltiplica di parecchie volte la
    // velocita!!!!!

    // a ogni giro, prendo due coppie di cifre piccole,
    // ne vreo una grande come quando moltiplico in colonna, e conservo il
    // riporto. in questo modo riduco le copie e creo un numero di lavoro con la
    // meta' delle cifre.
    // le difre grandi avanzano a mezza velocita'

    long fattore = POTENZA2;   // 2**30
    long fattore2 = POTENZA22; // 2**60
    long* n1 = nn1->cont;
    long* n2 = nn2->cont;
    long l1 = nn1->last;
    long l2 = nn2->last;
    long* lim1 = n1 + l1;
    long* lim2 = n2 + l2;
    arr* totale = create(NULL, l1 + l2, 0, 2, 30 * 2); // nn1->digits * 2);
    long* parziale = totale->cont;
    int count = 0; // cifre grandi
    for(long* ip1 = n1; ip1 < lim1; ip1 += 2, count++) {
        long riporto = 0;
        long* ir = parziale + count;
        long j1 = *ip1;
        long j2 = ip1 >= lim1 - 1 ? 0 : *(ip1 + 1); // dispari
        for(long* iq1 = n2; iq1 < lim2; iq1 += 2, ir++) {
            long k1 = *iq1;
            long k2 = iq1 >= lim2 - 1 ? 0 : *(iq1 + 1); // dispari
            long c1 = j1 * k1;
            long c2 = j2 * k1 + j1 * k2;
            long c3 = j2 * k2;
            long f7 = c2 >> 30;
            long f6 = (c2 & (fattore - 1)) << 30; // resto %
            long p = c1 + f6 + riporto + *ir;
            *ir = p & (fattore2 - 1); // resto %
            riporto = (p >> 60) + c3 + f7;
        }
        if(riporto > 0) {
            *ir++ += riporto;
        }
        totale->last = ir - parziale;
    }
    return totale;
}