#ifndef GALLINA_H
#define GALLINA_H

typedef struct {
    char* nome;
    int id;
} gallina, *gallina_ptr;
gallina_ptr crea_gallina(char* nome);
char* gallina_string(gallina_ptr p);
#endif
