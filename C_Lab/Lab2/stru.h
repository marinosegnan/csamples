
typedef struct u * uovoptr ;
typedef struct g {char * nome;  uovoptr *uova[10];} gallina;
typedef struct u { char *id; gallina * depositrice;} uovo;
typedef struct p {int count;gallina ** galline;} pollaio;
void crea();
void aggiungigallina(pollaio *p, char *nome);
void deponiuovo(char * nomegallina); // usa la data attuale e crea un nuovo id univoco
uovo ** preleva(int amount);
