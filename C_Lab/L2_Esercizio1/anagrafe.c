#include "anagrafe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char* s, char p1, char p2, int* inizio, int* fine)
{
    int pila = 0;
    int start = 1;
    int stop = -1;
    int len = strlen(s);
    for(int i = 0; i < len && stop < 0; s++, i++) {
        if(*s == p1) {
            if(pila == 0) {
                start = i;
                *inizio = i;
            }
            pila++;
        } else if(*s == p2) {
            pila--;
            if(pila == 0) {
                stop = i;
                *fine = i;
            }
        }
    }
    //  printf("start stop %d %d %d\n",start, stop, len);
    return 1;
}

anagrafe_ptr creanagrafe()
{
    anagrafe_ptr ret = malloc(sizeof(anagrafe));
    for(int i = 0; i < ANA_CAP; i++) {
        ret->cittadini[i] = NULL;
    }
    return ret;
}

char* anagrafe_to_string(anagrafe_ptr a)
{
    dynstringptr p = createstring(100);
    append(p, "{");
    append(p, "[");
    for(int i = 0; i < ANA_CAP && a->cittadini[i] != NULL; i++) {
        append(p, persona_to_string(a->cittadini[i]));
        append(p, ",");
    }
    append(p, "]");
    append(p, "}");
    return tocharstar(p);
}

int aggiungipersona(anagrafe_ptr a, persona_ptr p)
{
    for(int i = 0; i < ANA_CAP; i++) {
        if(a->cittadini[i] == NULL) {
            a->cittadini[i] = p;
            return 1;
        }
    }
    return 0;
}

int test_anagrafe()
{
    anagrafe_ptr a = creanagrafe();
    char nome[] = "nomen";
    for(int i = 0; i < 5; i++) {
        nome[4] = '0' + i;
        aggiungipersona(a, creapersona(nome, NULL, NULL));
    }
    printf("%s\n", anagrafe_to_string(a));
    //  match(anagrafe_to_string(a),'{','}');
    char* out = anagrafe_to_string(a);
    char* ror = anagrafe_to_string(a);
    printf("coincude?? %d\n", strcmp(out, ror));
    anagrafe_ptr anaa = anagrafe_from_string(out);
    printf("%s\n", out);
    char* out1 = anagrafe_to_string(anaa);
    printf("coincude?? %d\n%s\n", strcmp(out, out1), out1);
    return 0;
}

void crearray(persona* arra[], char* s)
{
    int parte = 0;
    int arriva = 0;
    match(s, '[', ']', &parte, &arriva);
    if(parte + 1 == arriva) {
        return; // vuoto
    }
    char* fine = s + arriva;
    s++; // skip [

    int index = 0;
    do {
        match(s, '{', '}', &parte, &arriva);
        //  *(s+arriva+1)='\0';
        arra[index++] = persona_from_string(s);
        s += arriva + 2;
    } while(s < fine);
}

anagrafe_ptr anagrafe_from_string(char* s)
{
    anagrafe_ptr ret = creanagrafe();
    s += 1; // skip {
    crearray(ret->cittadini, s);
    return ret;
}