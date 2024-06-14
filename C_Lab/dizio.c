#include <stdio.h>
#include <stdlib.h>

typedef struct n many, *manyptr;
struct n {
    manyptr* figli;
    int size;
    char val;
    char isword;
};

manyptr creamany(char val, int sz, int isword)
{
    manyptr ret = malloc(sizeof(many));
    if(ret != NULL) {
        manyptr* discendenti = malloc(sizeof(manyptr) * sz);
        if(discendenti != NULL) {
            for(int i = 0; i < sz; i++) {
                discendenti[i] = NULL;
            }
            ret->figli = discendenti;
            ret->val = val;
            ret->size = sz;
            ret->isword = isword;
        } else {
            // stampare errore, fare exir etc, deallocare se no..
            return NULL;
        }
    }
    return ret;
}

void addword(manyptr m, char* word)
{
    if(*word != '\0') {
        int ind = *word - 'a';
        if(m->figli[ind] == NULL) {
            m->figli[ind] = creamany(*word, 26, *(word + 1) == '\0');
        }
        addword(m->figli[ind], word + 1);
    }
}

void printmany(manyptr m, char word[], int ind)
{
    word[ind] = m->val;
    if(m->isword) {
        word[ind + 1] = '\0';
        printf("%s\n", word);
    } else {
        for(int i = 0; i < m->size; i++) {
            if(m->figli[i] != NULL) {
                printmany(m->figli[i], word, ind + 1);
            }
        }
    }
}

char buf[32];
void printroot(manyptr m)
{
    for(int i = 0; i < m->size; i++) {
        if(m->figli[i] != NULL) {
            printmany(m->figli[i], buf, 0);
        }
    }
}

char* parole[] = { "palo", "porta", "torta", "cane", "gatto" };

int testmany()
{
    manyptr root = creamany('\0', 26, 0);
    for(int i = 0; i < sizeof(parole) / sizeof(char*); i++) {
        addword(root, parole[i]);
    }
    printroot(root);
    return 0;
}

typedef void * jolly;

typedef struct {
long size;
long last;
void * elements;
} dynarray, *dynarrayptr;


//void prove(){
//    long a = 97;
//    jolly c = &a;
//    char * p = c;
//    printf("%s\n",c);
//    printf("%s\n",p);
//    jolly b = (jolly)a;     
//    char d = b;  
//    char e = (char) b;
//    long f = (long) b;
//    char g = (char) f;
//    printf("%c %c %c %c\n",d,e,f,g);
//    long l = 67568765565;
//    jolly vl = &l;
//    char * er = vl;
//    printf("%s\n",er);
//}

void prove1(){
    long a = 97;
    void * c = &a;
    char * p = c;
    printf("%s\n",c);
    printf("%s\n",p);
    void * b = (void*)a;     
    char d = b;  
    printf("%c\n",d);
    long l = 67568765565;
    void* vl = &l;
    printf("%s\n",(char*) vl);
}
int main(int argc, char* argv[])
{
    printf("inizio test albero-dizionario\n");
    int result = testmany();
    prove1();
    exit(result);
}
