#ifndef TEMPI_H
#define TEMPI_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double diff(struct timeval *tv1, struct timeval *tv2);

void miotempo(char *msg);

#endif
