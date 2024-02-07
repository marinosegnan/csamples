#include <stdio.h>
#include <limits.h>
#include <stdint.h>


/* esempio di buffer circolare con array fisso, usare malloc banale */

#define SIZE 10
#define SUBT ((UINT_MAX / SIZE) -1)
//#define SUBT 10  // per testing
#define LIM (SUBT*SIZE)

unsigned buf[SIZE];
unsigned first =0, last=0;

void add(int el){
    if (last-first > SIZE){
        printf("pieno\n");
    } else {
        buf[last++%SIZE] = el;
        if (first > LIM){
            last -= LIM;
            first -= LIM;
            printf ("abbasso %d %d\n",first,last);
        }
    }
}

int rem(){
    if (first >= last){
        printf("vuoto\n");
    } else {
        int ret = buf[first++%SIZE];
        return ret;
    }
}

void bu(){
for (int i=0;i< 500;i++){
    if (i%2==0){
        add(i);
    } else {
        printf("R%d\n",rem());
    }
}
printf("DIM=%d %d %d %u %u\n",first,last,last-first,SUBT, UINT_MAX - LIM);
printf("size_max = %zu\n", SIZE_MAX);
}