
#include "dynstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dynstringptr createstring(int capacity)
{
    // crea e segnala che e' allocata (per eventuale free)

    dynstringptr ret = malloc(sizeof(dynstring)); // check error
    ret->content = capacity > 0 ? malloc(sizeof(char) * capacity) : NULL;
    ret->capacity = capacity;
    ret->last = 0;
    ret->allocated = 1;
    return ret;
}

void append(dynstringptr s, char* s2)
{
    // per '\0' finale, non inserito di default, alloco sempre un carattere in piu' della caopacity
    // non controlla out of memory
    int len = strlen(s2);
    if(s->content == NULL) {
        s->content = malloc(sizeof(char) * (len + 1));
        s->capacity = len;
        s->last = 0;
    } else if(s->capacity - s->last < len) { // gia' allocato ma piccolo
        do {
            s->capacity *= 2;
        } while(s->capacity - s->last < len);
        s->content = realloc(s->content, sizeof(char) * (s->capacity + 1));
    }
    strncpy(s->content + s->last, s2, len);
    s->last += len;
}

void reset(dynstringptr p) { p->last = 0; }

char* tocharstar(dynstringptr p)
{
    *(p->content + p->last) = '\0';
    return p->content;
}

int cancelladynstr(dynstringptr p)
{
    if(p->allocated) {
        free(p->content);
        free(p);
        return 1;
    } else {
        return 0;
    }
}
char* mydup(char* s, int len)
{
    char* ret = malloc(sizeof(char) * (len + 1));
    strncpy(ret, s, len);
    *(ret + len + 1) = '\0';
    return ret;
}

int testdynstring()
{
    char* prove[] = { " aaa", "bb", "jhsdfkjhksdjhjfhjhkfjksdfjhkjhksf", "kkjkjj" };
    char* concat = " aaabbjhsdfkjhksdjhjfhjhkfjksdfjhkjhksfkkjkjj";
    dynstringptr p = createstring(1);
    for(int i = 0; i < MYSIZE(prove); i++) {
        append(p, prove[i]);
    }
    char* res = tocharstar(p);
    printf("res=%d", strcmp(res, concat));
    printf(" %d\n", cancelladynstr(p));
    dynstring s = { NULL, 0, 0, 0 };
    for(int i = 0; i < sizeof(prove) / sizeof(prove[0]); i++) {
        append(&s, prove[i]);
    }
    res = tocharstar(&s);
    printf("res=%d %d\n", strcmp(res, concat), cancelladynstr(&s));
    return 0;
}
