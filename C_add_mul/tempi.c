#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <tempi.h>

struct timeval* oldtv = NULL;

double diff(struct timeval* tv1, struct timeval* tv2)
// calcola differenza di due tempi trasformata in secondi
{
    long due = tv2->tv_sec * pow(10, 6) + tv2->tv_usec;
    long uno = tv1->tv_sec * pow(10, 6) + tv1->tv_usec;
    return (due - uno) / pow(10, 6);
}

void miotempo(char* msg)
// stampa la differenza di tempo fra la chiamata e quella precednte
// ed eventualmente un messaggio
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0) {
        printf("%s\n", "errore");
        return;
    }
    if(oldtv != NULL) {
        if(msg != NULL) {
            printf("%s tempo= %f\n", msg, diff(oldtv, &tv));
        }
    } else {
        // prima chiamata o reset
        oldtv = malloc(sizeof(struct timeval));
    }
    oldtv->tv_sec = tv.tv_sec;
    oldtv->tv_usec = tv.tv_usec;
}

