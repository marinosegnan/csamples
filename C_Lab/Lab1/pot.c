#include <stdio.h>

#define MYMAX  10000

typedef struct {} pluto; // facciamo finta che serva qui

pluto ppp;

void printpotenze(int num,int esp){
for (int u = num; u < MYMAX && esp > 0; u = u*num, esp--){
printf("%d\n",u);
}
}
