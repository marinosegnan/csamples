#include <stdarg.h>
#include <stdio.h>

void variabile(int num, ...)
{
    // notare che il primo arg dice quanti ce ne sono
    // occorre anche sapere che tipo hanno, chi ce lo dice?
    // qui si assume int altrimenti se fossero di tipi diversi
    // occorrerebbe dirlo. ne vale la pena solo in pochi casi, es printf()
    printf("n_args= %d\n", num);
    va_list ptr; // puntatore alla lista degli argomenti

    if(num > 0) {
        va_start(ptr, num); // il puntatore fa ora riferimento al
                            // primo elem dei param opzionali
        while(num-- > 0) {
            printf("%d\n", va_arg(ptr, int));
        }
    };
}

int main(int argc, char** argv)
{
    printf("hello world\n");
    variabile(0, 4, 5);
    variabile(5, 1, 2, 3, 4, 5);
    return 0;
}