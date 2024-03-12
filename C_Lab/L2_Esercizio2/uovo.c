#include <stdio.h>
#include <stdlib.h>
#include <uovo.h>

int last_uovo = 0;

uovo_ptr creauovo()
{
    uovo_ptr ret = malloc(sizeof(uovo));
    ret->id = last_uovo++;
    return ret;
}

char* uovo_string(uovo_ptr p)
{
    char* ret = malloc(50);
    sprintf(ret, "U(%d)", p->id);
    return ret;
}