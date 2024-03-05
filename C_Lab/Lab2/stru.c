#include <stdlib.h>
#include <stdio.h>
//#include <stru.h>

void crea(){
    srand(1000);
    for (int i =0;i < 10;i++){
        printf("%d\n",rand()%4);
    }
    
}