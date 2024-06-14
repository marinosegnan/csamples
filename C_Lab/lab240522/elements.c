#include <elements.h>
#include <stdlib.h>

elem* crea(void* content)
{
    elem* ret = malloc(sizeof(elem));
    if(ret != NULL) {
        ret->next = NULL;
        ret->mytype = content;
    }
    return ret;
}
