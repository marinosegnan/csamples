#ifndef PERSONA_H
#define PERSONA_H

#include "dynstring.h"

typedef struct {
    char* name;
    char* madre;
    char* padre;
} persona, *persona_ptr;

persona_ptr creapersona(char* name, char* madre, char* padre);
void liberapersona(persona_ptr p);

persona_ptr persona_from_string(char* s);
char* persona_to_string(persona_ptr a);
int test_persona();

#endif