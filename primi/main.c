#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void miotempo(char* s);

// 2310 fino 11, 30030  fino a 13 ,510510 fino a 17, 9699690 fino 19
// stramissimo che 30030 sia la dimensione ottimale,
// piu' o meno primi precalcolati peggiora moltissimo

#define SZ 30030

#define PRIMI 1000000

#define QUANTIPRIMI 7
// 100 e' il numero di file per stampare out, la dimensione TOTALE adesso e 10**9
//  ultimo numero = 22801763477
// CPU tempo= 159.850128

// dato un intervallo di interi, la maggior parte (80%) non e'
// prima perche' multipla dei primi numeri primi (in tal caso 2..13)

long giusti[SZ];
long indici[SZ];
// incrementi contiene la distanza del prossimo numero primo dall'attuale
long incrementi[SZ];
long firstprime;
long lastprime;
long last;
long massimadistanza;

long primi[PRIMI];
long primiwork[PRIMI];

long numeri[SZ];
long salvi[SZ];
long menouno[SZ];

long prod = 1;

void salvaprimi(long* pri, long starting, long quanti, int binary)
{
    char buf[64];
    sprintf(buf, "PRIMI/primi_%ld_%ld.%s", starting, quanti, binary ? "bin" : "txt");
    FILE* ff = fopen(buf, "w");
    if(binary) {
        fwrite(pri, sizeof(long), quanti, ff);
    } else {
        for(int k = 0; k < quanti; k++) {
            fprintf(ff, "%ld\n", pri[k]);
        }
    }
    fclose(ff);
    sprintf(buf, "PRIMI/primi_%ld_%ld.offset", starting, quanti);
    ff = fopen(buf, "w");

    for(int k = 1; k < quanti; k++) {
        long temp = pri[k] - pri[k - 1];
        fprintf(ff, "%ld\n", pri[k] - pri[k - 1]);
        if(temp > massimadistanza) {
            massimadistanza = temp;
        }
    }
    fclose(ff);
    printf("salvati: %ld\n", starting);
}

FILE* partenze;
unsigned char distanze[PRIMI];
FILE* previous;
long lastprevious;

void fillprevious(long quanti)
{
    if(previous) {
        distanze[quanti - 1] = 0;
        fwrite(distanze, sizeof(char), quanti, previous);
        fclose(previous);
    }
}

void salvaoffset(long* pri, long starting, long quanti)
{
    // salva come offset un byte che rappresenta la distanza /2 di un primo dal prossimo

    fprintf(partenze, "%ld: %ld\n", starting, pri[0]); // aggiungi in un file di partenze il primo numero
    char buf[64];
    if(starting > 0) {
        distanze[quanti - 1] = pri[0] - lastprevious;
        // scrivi la distanza dal numero emmorizzato nel file successivo
        if(distanze[quanti - 1] > massimadistanza) {

            massimadistanza = distanze[quanti - 1];
            if(massimadistanza > 511) {
                fprintf(stderr, "errore in distanza > 1 byte: %ld\n", massimadistanza);
                exit(1);
            }
        }
        fwrite(distanze, sizeof(char), quanti, previous);
        fclose(previous);
    }
    sprintf(buf, "PRIMI/primi_%ld_%ld.offset", starting, quanti);
    previous = fopen(buf, "w");
    for(int k = 1; k < quanti; k++) {
        long temp = pri[k] - pri[k - 1];
        if(temp > massimadistanza) {
            massimadistanza = temp;
            if(massimadistanza > 511) {
                fprintf(stderr, "errore in distanza > 1 byte: %ld\n", massimadistanza);
                exit(1);
            }
        }
        // cosi fino a distanze di 512 basta un byte
        // diventa 0 solo per i primi primi: 1,2,3, che hanno distanza == 1!
        distanze[k - 1] = (unsigned char)(temp / 2);
    }
    lastprevious = pri[quanti - 1];
    printf("salvati: %ld\n", starting);
}

void leggiprimi(long* ret, long starting, long quanti, int binary)
{
    // leggi i primi, scritti come testo uno per linea
    // oppure come blocco di byte, ci si aspetta che il nome file contenga
    // indice del primonumero e quanti sono meorizzati
    char buf[64];
    sprintf(buf, "PRIMI/primi_%ld_%ld.%s", starting, quanti, binary ? "bin" : "txt");
    FILE* gg = fopen(buf, "r");
    long unu = 0;
    if(binary) {
        unu = fread(ret, sizeof(long), quanti, gg);
    } else {
        for(int k = 0; k < quanti; k++) {
            unu = fscanf(gg, "%ld\n", &ret[k]);
        }
    }
    unu++;
    ;
    fclose(gg);
}

void leggioffset(long* ret, long starting, long quanti)
{
    printf("leggioffset DA  FARE\n");
    exit(1);
    // dovrebbe leggere :
    // un numero di partenza dal file partenze_<LONG>.txt
    // andare a cercare il file <primi_<LONG>.offset
    // sommare la distanza dalla partenza , aggiungendo via via i byte,
    // se parto da primo A1, secondo sara A2 = A1.(byte all'offset relativo)
    // creando una catena di valori si risparmia usando 1 byte anziche' 8 per i LONG
    // ma funziona solo se offset < 512, ottimizzo dividendo per 2
    // perche' offset sempre pari tranne che per 1,2,3

    char buf[64];
    sprintf(buf, "PRIMI/primi_%ld_%ld.offset", starting, quanti);
    FILE* gg = fopen(buf, "r");
    long unu = fread(ret, sizeof(unsigned char), quanti, gg);
    printf("letti %ld\n",unu);
    fclose(gg);
}

void initmask()
{
    primi[0] = 1;
    primi[1] = 2;
    primi[2] = 3;
    primi[3] = 5;
    primi[4] = 7;
    primi[5] = 11;
    primi[6] = 13;

    //    primi[7] = 17;
    //     primi[8] = 19;
    long numer[SZ];
    for(int r = 0; r < SZ; r++) {
        numer[r] = 0;
    }
    firstprime = 1;
    lastprime = QUANTIPRIMI;
    for(int i = firstprime; i < lastprime; i++) {
        long pp = primi[i];
        prod *= pp;
        for(int r = 0; r < SZ; r += pp) {
            numer[r] = -1;
        }
    }
    int cn = 0;
    for(int u = 0; u < SZ; u++) {
        // copia compattati i numeri che sono candidati primi
        if(numer[u] != -1) {
            giusti[cn] = u;
            cn++;
        }
    }
    last = cn;
    printf("PROD=%ld giusti =%f \n", prod, (cn * 1.0) / SZ);
    for(long a = 0; a < SZ; a++) {
        menouno[a] = -1;
    }
}

long* scorta = NULL;

void aggiornaeratosimple(long parte)
// piu' semplice e piu' veloce!
{
    // segna da quali ripartire per la prossima finestra
    // a blocchi di SZ candidati
    memcpy(numeri, giusti, last * sizeof(long));
    if(scorta == NULL) {
        long qua = 0;
        for(; qua < last; qua++) {
            long val = giusti[qua];
            menouno[val] = qua;
        }
        scorta = menouno;
    }
    memcpy(salvi, scorta, SZ * sizeof(long));
    long arrivo = parte + SZ;
    long limite = (long)sqrt(arrivo);
    for(int p = QUANTIPRIMI; p < SZ; p++) { // primi[7] === 17 !
        long pp = primi[p];
        if(pp == 0 || pp > limite) {
            break;
        }
        long starte = pp - (parte % pp);
        if(starte % 2 == 0) {
            starte += pp; // e' pari, non sara' primo lo saltiamo
        }

        long incremento = 2 * pp;
        for(int g = starte; g < SZ; g += incremento) {
            int index = salvi[g];
            if(index >= 0) {
                numeri[index] = 0;
                salvi[g] = -1;
            }
        }
    }
}

void baseloop(long* primearray, long iii, long* ppartenza, long* pposi, long buono)
{
    long partenza = *ppartenza;
    long posi = *pposi;
    long newval, curr;
    while(iii < PRIMI) {
        if(posi >= last) {
            partenza = partenza + SZ;
            aggiornaeratosimple(partenza);
            posi = 0;
        }
        if((newval = numeri[posi++]) <= 0) {
            continue;
        }
        curr = newval + partenza;
        if(!buono || curr >= buono) {
            primearray[iii++] = curr; //+partenza;
        }
        long g = curr - (partenza % curr);
        if(g % 2 == 0) {
            g += curr;
        }
        for(; g < SZ; g += 2 * curr) {
            int index = salvi[g];
            if(index >= 0) {
                numeri[index] = 0; // azzeralo nella lista compattata
                salvi[g] = -1;
            }
        }
    }
    printf(" ultimo numero = %ld\n", curr);
    *ppartenza = partenza;
    *pposi = posi;
}

long eratostene1(long* parte)
{
    // inizializza un array coi primi numeri primi;
    // serve per fare i loop successivi perche' saranno eliminati molto piu' in distanza
    initmask();
    aggiornaeratosimple(*parte);
    long posi = 1;
    // imoportante! il primo giro il primo
    // elemnto contiene 1, lo dobbiamo scartare!!!
    baseloop(primi, QUANTIPRIMI, parte, &posi, 0);
    return posi;
}

void eratostene2(long richiesti)
{
    // molto simile, ma stampa a pezzi i primi, 1 ogni PRIMI, in un file, e poi crea dei file cogli offset
    // cosi usiamo un byte per ogni primo, al prezzo di doverlo calcolare
    long partenza = 0;
    long posi = eratostene1(&partenza);

    // caricato array dei primi primi: ora si usa una copia di lavoro
    // da scaricare su file
    salvaoffset(primi, 0, PRIMI);
    // loop simile a eratostene1 ma dovrebbe salvare su file i primi a blocchi per evitare out of memory
    // non perfetta, ma si basa sul fatto di tenere in memoria quelli fino radice(N)
    // in quesat versione, continuiamo ad esaminare quelli gia' caricati, la cosa del primo loop,
    // cosicche' non reinizializziamo 'posi' a 0

    for(long loop = PRIMI; loop < richiesti; loop += PRIMI) {
        baseloop(primiwork, 0, &partenza, &posi, 0);
        salvaoffset(primiwork, loop, PRIMI);
    }
}

void eratostene3(long distante, long howma)
// howma e' in genere un multiplo dei PRIMI di base
// genera howma primi a partire dal intero arbitrario 'distante'
{
    // non controlliamo overflow!!!
    long partenza = 0;
    long posi = eratostene1(&partenza);
    long valmax = primi[PRIMI - 1] * primi[PRIMI - 1];
    if(valmax < distante) {
        printf("Erroe, cerco primi troppo grandi, aumenta la base %ld %ld\n", valmax, distante);
        exit(1);
    }
    // caricato array dei primi primi: ora si usa una copia di lavoro
    // da scaricare su file
    salvaoffset(primi, 0, PRIMI);
    // loop simile a eratostene1 ma dovrebbe salvare su file i primi a blocchi per evitare out of memory
    // non perfetta, ma si
    // basa sul fatto di tenere in memoria quelli fino radice(N)
    // long verapartenza = distante;
    partenza = distante - (distante % SZ); // sincronizza
                                             // carica candidadati un po' prima della partenza richiesta
                                             // e' uno spreco molto piccolo confronto al resto
    aggiornaeratosimple(partenza);
    posi = 0;
    for(long loop = 0; loop < howma; loop += PRIMI) {
        baseloop(primiwork, 0, &partenza, &posi, distante); // verapartenza);
        salvaoffset(primiwork, loop, PRIMI);
    }
}

int main(int argc, char** argv)
{
    printf("opzioni: 0= genera solo primi (10**6)\n");
    printf("opzioni: 1= genera primi (10**6)  escrivi i file di testo\n");
    printf("opzioni: 2= genera tutti primi (10**6) spec da param 2 ( es 10) genera 10 milioni\n");
    printf("e salva su file con offset, piu' partenze ogni 10*86\n");
    printf("opzioni: 3= i i primi > parametro 2 e negerane k (parametro 3)\n\n");

    int opzione = 0;
    int cicli = 0;
    int inizio = 0;
    int quanti = 0;
    char buf[64];
    if(argc > 1) {
        opzione = atoi(argv[1]);
    }
    if(opzione == 2) {
        cicli = atoi(argv[2]);
    }
    if(opzione == 3) {
        inizio = atoi(argv[2]);
        quanti = atoi(argv[3]);
    }
    switch(opzione) {
    case 0:
    case 1:
        long u1 = 0;
        miotempo(NULL);
        eratostene1(&u1);
        miotempo("fine");
        if(opzione == 1) { // stampa la tabella di base come testo
            sprintf(buf, "PRIMI/primi_%ld.txt", (long)PRIMI);
            FILE* ff = fopen(buf, "w");
            for(int k = 0; k < PRIMI; k++) {
                fprintf(ff, "%ld\n", primi[k]);
            }
            fclose(ff);
        }
        break;
    case 2:
        sprintf(buf, "PRIMI/partenze_%ld.txt", (long)PRIMI);
        partenze = fopen(buf, "a+");
        miotempo(NULL);
        // simile a opzione 0, ma ripeti per cicli volte
        eratostene2(cicli * PRIMI);
        miotempo("fine");
        fclose(partenze);
        fillprevious(PRIMI); // completa ultimo file coll' ultimissimo offset
        printf("massimadistanza tra primi: %ld\n", massimadistanza);
        break;
    case 3:
        sprintf(buf, "PRIMI/partenze_%ld.txt", (long)PRIMI);
        partenze = fopen(buf, "a+");
        miotempo(NULL);
        // parti dal primo numero primo >= al primo parametro, quantita' = secondo parametro
        // puo' dare erroe, se non abbiamo primi a sufficienza
        // fino alla radice del secondo parametro
        //  eratostene3(438197560000,1000000); -> errore
        // il seguente genera il secondo milione di primi
        eratostene3(inizio, quanti); //( 15485858, 1000000);
        miotempo("fine");
        fillprevious(PRIMI);
        fclose(partenze);
        printf("massimadistanza tra primi: %ld\n", massimadistanza);
        break;
    }
    return 0;
}

// alcune utility su tabella

void fattorizza(long num)
{
    while(num > 1) {
        for(int i = 1; i < 1000; i++) {
            long ris = num / primi[i];
            if(ris * primi[i] == num) {
                printf("%ld,", primi[i]);
                num = ris;
                break;
            }
        }
    }
    printf("\n");
}

void tuttodiverso(long num)
{
    // stupida funzione che guarda se un primo ha tutte difre diverse
    // ovviamente va solo fino a lunghezza di 10 cifre
    long save = num;
    int cifre[10];
    for(int i = 0; i < 10; i++) {
        cifre[i] = 0;
    }
    while(num > 0) {
        int v = num % 10;
        if(cifre[v] == 0) {
            cifre[v] = 1;
        } else {
            return;
        }
        num = num / 10;
    }
    printf("%ld\n", save);
}
