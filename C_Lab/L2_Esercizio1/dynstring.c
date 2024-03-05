#include "dynstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dynstringptr createstring(int capacity)
{
    dynstringptr ret = malloc(sizeof(dynstring)); // check error
    ret->content = malloc(sizeof(char) * capacity);
    ret->capacity = capacity;
    ret->last = 0;
    return ret;
}

void append(dynstringptr s, char* s2)
{
    int len = strlen(s2);
    if(s->capacity - s->last < len) {
        do {
            s->capacity *= 2;
        } while(s->capacity - s->last < len);
        s->content = realloc(s->content, sizeof(char) * s->capacity);
    }
    strncpy(s->content + s->last, s2, len);
    s->last += len;
}

void reset(dynstringptr p) { p->last = 0; }

char* tocharstar(dynstringptr p)
{
    *(p->content + p->last) = '\0'; // potenziale errore! occorre verificare se c''e spazio
    return p->content;
}

void cancelladynstr(dynstringptr p)
{
    free(p->content);
    free(p);
}

int testdynstring()
{
    char* prove[] = { " aaa", "bb", "jhsdfkjhksdjhjfhjhkfjksdfjhkjhksf", "kkjkjj" };
    char* concat = " aaabbjhsdfkjhksdjhjfhjhkfjksdfjhkjhksfkkjkjj";
    dynstringptr p = createstring(1);
    for(int i = 0; i < sizeof(prove) / sizeof(prove[0]); i++) {
        append(p, prove[i]);
    }
    char* res = tocharstar(p);
    printf("res=%d\n", strcmp(res, concat));
    return 0;
}
