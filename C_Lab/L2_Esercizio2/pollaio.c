#include <pollaio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_gallina(pollaio_ptr p, gallina_ptr g)
{
    for(int i = 0; i < sizeof(p->galline) / sizeof(p->galline[0]); i++) {
        if(p->galline[i] == NULL) {
            p->galline[i] = g;
            return;
        }
    }
}

pollaio_ptr crea_pollaio()
{
    pollaio_ptr ret = malloc(sizeof(pollaio));
    for(int i = 0; i < sizeof(ret->galline) / sizeof(ret->galline[0]); i++) {
        ret->galline[i] = NULL;
    }
    for(int i = 0; i < sizeof(ret->uova) / sizeof(ret->uova[0]); i++) {
        ret->uova[i] = NULL;
    }
    return ret;
}

char buf[10000];

char* pollaio_string(pollaio_ptr p)
{
    char* cur = buf;
    for(gallina** g = p->galline; *g != NULL; g++) {
        char* s = gallina_string(*g);
        int l = strlen(s);
        strncpy(cur, s, l);
        cur += l;
        *cur++ = ' ';
    }
    *cur = '\0';
    return buf;
}

int test_pollaio()
{
    pollaio_ptr pt = crea_pollaio();
    add_gallina(pt, crea_gallina("pina"));
    add_gallina(pt, crea_gallina("gina"));
    add_gallina(pt, crea_gallina("nina"));
    add_gallina(pt, crea_gallina("nina"));
    printf("%s\n", pollaio_string(pt));
    return 0;
}