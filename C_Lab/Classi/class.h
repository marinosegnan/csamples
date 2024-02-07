
//per definire ricorsivamente occorre usare <struct pippo> {struct pluto...} veronome;
// e viceversa!


typedef struct funz{
    void* (*metodo)();
    void * parametri[10];
    void *retval;
    char *name;
} oggettofunzione;

typedef struct ogge{
    void* ob;
    struct clas *myclass;
} oggetto;

typedef struct clas {
    char name [20];
    struct ogge *funzioni[10];
    char *funcname[10];
    char *(*astringa)();
    int (*confronta)();
} classe;

extern classe funzione,cl1,cl2;

void * creaoggetto(void *elem);
void * creaoggetto1(void *elem, char *clname);
void * creaoggetto2(void *elem);
void * creafunzione(void *elem, char *nam);
char *astringa(oggetto *o);
void stampafunclasse (classe *c);
void addfunzione(classe *c,oggetto *o, char *nomefunc);
void *esegui(oggetto *o, char *met);