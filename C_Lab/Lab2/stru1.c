#include <stdlib.h>
#include <stdio.h>
#include <stru1.h>

void crea1(){
    pollaio po;
    po.count = 10;
    po.galline = malloc(10*sizeof(gallina*));
    srand(1000);
    for (int i =0;i < 10;i++){
        printf("%d\n",rand()%4);
    }
}

void aggiungigallina(pollaio *p, char *nome){
    
}

void deponiuovo(char * nomegallina) // usa la data attuale e crea un nuovo id univoco
{
    
}

uovo ** preleva(int amount){
    
}