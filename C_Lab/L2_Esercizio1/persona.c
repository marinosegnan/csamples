#include "persona.h"

#include <stdlib.h>

personaptr creapersona(char* name, char* madre, char* padre)
{
    personaptr ret = malloc(sizeof(persona));
    ret->name = name;
    ret->madre = madre;
    ret->padre = padre;
    return ret;
}

void cancellapersona(personaptr p) { free(p); }
