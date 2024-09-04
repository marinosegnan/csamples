#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct timeval* oldtv = NULL;

double diff(struct timeval* tv1, struct timeval* tv2)
{
    long due = tv2->tv_sec * pow(10, 6) + tv2->tv_usec;
    long uno = tv1->tv_sec * pow(10, 6) + tv1->tv_usec;
    return (due - uno) / pow(10, 6);
}

void miotempo(char* msg)
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
        // prima chiamata
        oldtv = malloc(sizeof(struct timeval));
    }
    oldtv->tv_sec = tv.tv_sec;
    oldtv->tv_usec = tv.tv_usec;
}
