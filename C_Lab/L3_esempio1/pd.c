#include "a.h"

#include <stdio.h>

mia qq = { 2, 2.78 };

long retlong()
{ // funziona senza prototipo
    return 88;
}

pdcomplex noexport1()
{ // funziona solo con prototipo causa return di non int
    printf("%p export1 \n", &qq);
    return &qq;
}

void noexport2(pdcomplex pp)
{ // funziona senza prototipo
    printf("%p %p\n", &qq, pp);
    printf("differenti ? %d\n", pp == &qq);
    printf("a=%d\n", pp->a); // crash
}
