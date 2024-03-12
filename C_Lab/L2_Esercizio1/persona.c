#include "persona.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

persona_ptr creapersona(char* name, char* madre, char* padre)
{
    persona_ptr ret = malloc(sizeof(persona));
    ret->name = strdup(name);
    ret->madre = madre != NULL ? strdup(madre) : NULL;
    ret->padre = padre != NULL ? strdup(padre) : NULL;
    return ret;
}

void cancellapersona(persona_ptr p) { free(p); }

void appendfield(dynstringptr p, char* s)
{
    if(s == NULL) {
        append(p, "NULL");
    } else {
        append(p, "\"");
        append(p, s);
        append(p, "\"");
    }
}
char* persona_to_string(persona_ptr a)
{
    dynstringptr p = createstring(100);
    append(p, "{");
    appendfield(p, a->name);
    append(p, ",");
    appendfield(p, a->madre);
    append(p, ",");
    appendfield(p, a->padre);
    append(p, ",");
    append(p, "}");
    return tocharstar(p);
}

char* getfieldstring(char* s)
{ // per ora stringa
    //   printf("campo==%s\n",s);
    char* ret = s;
    while(*ret != ',') {
        ret++;
    }
    return ret - 1;
}

persona_ptr persona_from_string(char* s)
{
    // artigianale ma si potrebbe estendere ai vari tipi possibili
    s++; // togli {
    char *name = NULL, *madre = NULL, *padre = NULL;
    char* curr = getfieldstring(s);
    if(*s == '\"') {
        name = mydup(s + 1, curr - s - 1);
    }
    s = curr + 2;
    curr = getfieldstring(s);
    if(*s == '\"') {
        madre = mydup(s + 1, curr - s - 1);
    }
    s = curr + 2;
    curr = getfieldstring(s);
    if(*s == '\"') {
        padre = mydup(s + 1, curr - s - 1);
    }
    return creapersona(name, madre, padre);
}

int test_persona()
{
    persona_ptr a = creapersona("a", NULL, "bb");
    char* val = persona_to_string(a);
    printf("%s\n", val);
    a = persona_from_string(val);
    char* fine = persona_to_string(a);
    printf("%s\n", fine);
    return 0;
}