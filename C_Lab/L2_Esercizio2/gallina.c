#include <gallina.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int last_gallina = 0;

gallina_ptr crea_gallina(char* nome)
{
    gallina_ptr ret = malloc(sizeof(gallina));
    ret->id = last_gallina++;
    ret->nome = malloc(strlen(nome) + 1);
    strcpy(ret->nome, nome);
    return ret;
}

char* gallina_string(gallina_ptr p)
{
    char* ret = malloc(50);
    sprintf(ret, "G(%s,%d)", p->nome, p->id);
    return ret;
}