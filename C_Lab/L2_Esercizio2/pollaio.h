#ifndef POLLAIO_H
#define POLLAIO_H
#include <gallina.h>
#include <uovo.h>

typedef struct {gallina  *galline[100];
uovo *uova[1000];
} pollaio ,*pollaio_ptr;
    
    int test_pollaio();
    
#endif