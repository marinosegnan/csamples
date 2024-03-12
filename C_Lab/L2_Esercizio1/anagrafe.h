#ifndef ANAGRAFE_H
#define ANAGRAFE_H

#include "persona.h"
#define ANA_CAP 100

typedef struct {
    persona_ptr cittadini[ANA_CAP];
} anagrafe, *anagrafe_ptr;

anagrafe_ptr creanagrafe();
void liberanagrafe(anagrafe_ptr p);
int aggiungipersona(anagrafe_ptr a, persona_ptr p);
persona_ptr cercapersona(char* nome); // esiste dentro anagrafe
persona_ptr getmadre(persona_ptr p);
persona_ptr getmadre(persona_ptr p);
int sorellafratello(persona_ptr p1, persona_ptr p2); // trovare parentela, si potrebbe anche col nome

anagrafe_ptr anagrafe_from_string(char* s);
char* anagrafe_to_string(anagrafe_ptr a);

int test_anagrafe();

#endif