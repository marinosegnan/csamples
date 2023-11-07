#include <assert.h>
#include <binario.h>
#include <listadt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tempi.h>
//#include <sys/param.h>
#include <visitebin.h>

node* createnode(adt* e, node* parent)
{
    node* v = malloc(sizeof(node));
    v->left = NULL;
    v->right = NULL;
    v->up = parent;
    v->elem = e;
    v->branchsize = 1;
    v->height = 1;
    return v;
}

node* adjust(node* curr)
{
    // rimuovi parametro dall'albero
    // tanti casi :
    // se un solo figlio attacco quello all'antenato
    // se due figli attacco il sx, e il dx come figlio del sx tutto a destra

    node* tmpL = curr->left;
    node* tmpR = curr->right;
    node* target = NULL;
    int duedisc = 0;
    if(tmpL != NULL && tmpR == NULL) {
        target = tmpL;
    } else if(tmpR != NULL && tmpL == NULL) {
        target = tmpR;
    } else if(tmpR != NULL && tmpL != NULL) {
        target = tmpL;
        duedisc = 1;
    }
    node* nonno = curr->up;
    if(nonno != NULL) {           // non e' la root
        if(nonno->left == curr) { // sono a sx o dx?
            nonno->left = target;
        } else {
            nonno->right = target;
        }
    }
    if(target != NULL) {
        target->up = nonno; // puo essere NULL, radice
    }
    if(duedisc) {
        // 2 discendenti:
        // il dx diventa disc del sx tutto a dx
        // aggiorna size di tutto il ramo

        long siz = tmpR->branchsize;
        node* ant = tmpL;
        while(ant->right != NULL) {
            ant->branchsize += siz;
            ant = ant->right;
        }
        ant->branchsize += siz;
        ant->right = tmpR;
        tmpR->up = ant;
    }
    // togli 1 a branchsize fino radice
    for(node* tmp = nonno; tmp != NULL; tmp = tmp->up) {
        tmp->branchsize -= 1;
    }
    free(curr);
    return nonno;
}

void checkTree(node* n)
{
    // verifica connessione nodi tramite "up"
    if(n != NULL) {
        if(n->left != NULL) {
            assert(n->left->up == n);
            checkTree(n->left);
        }
        if(n->right != NULL) {
            assert(n->right->up == n);
            checkTree(n->right);
        }
    }
}

node* removeAdt(node* curr, adt* e)
{
    if(curr == NULL) {
        return NULL;
    }
    int res = compare(e, curr->elem);
    if(res == 0) {
        return adjust(curr);
    } else {
        if(res < 0) {
            return removeAdt(curr->left, e);
        } else {
            return removeAdt(curr->right, e);
        }
    }
}

node* insertsz(node* curr, adt* e)
{
    // ha un po piu' di casi, ma crea anche partendo da albero vyoto
    // e aggiorna size del ramo
    node* retval = NULL;
    if(curr == NULL) {
        printf("insertsz crea ROOT\n");
        retval = createnode(e, NULL);
    } else {
        int res = compare(e, curr->elem);
        if(res == 0) {
            return NULL; // gia' presente
        } else if(res < 0) {
            if(curr->left != NULL) {
                retval = insertsz(curr->left, e);
            } else {
                curr->left = createnode(e, curr);
                retval = curr->left;
            }
        } else { // >0
            if(curr->right != NULL) {
                retval = insertsz(curr->right, e);
            } else {
                curr->right = createnode(e, curr);
                retval = curr->right;
            }
        }
    }
    if(retval != NULL && curr != NULL) { // creato un nodo non root
        curr->branchsize += 1;
    }
    return retval;
}

adt** linearr(node* n, adt** curr)
{
    // linearizza creando array (preallocato)
    if(n->left != NULL) {
        curr = linearr(n->left, curr);
    }
    *curr++ = n->elem;
    if(n->right != NULL) {
        curr = linearr(n->right, curr);
    }
    return curr;
}

adelem* linearizza(node* curr, adelem* ultimo)
{
    // linearizza creando lista
    adelem* tot = ultimo;
    if(curr->left != NULL) {
        tot = linearizza(curr->left, tot);
    }
    tot = add(tot, curr->elem);
    if(curr->right != NULL) {
        tot = linearizza(curr->right, tot);
    }
    return tot;
}

char buf[2000];

void printTree(node* curr, int indent)
{
    if(indent > 1000) {
        printf("too big indent truncate to: 1000\n");
        indent = 1000;
    }
    if(curr != NULL) {
        char* p = buf + indent;
        *p-- = '\0';
        while(p >= buf) {
            *p-- = ' ';
        }
        printf("%s%s\n", buf, tostr(curr->elem));
        printTree(curr->left, indent + 4);
        printTree(curr->right, indent + 4);
    }
}

long treeSize(node* curr)
{
    // calcola e memorizza la dimensione di ogni branch
    if(curr == NULL) {
        return 0;
    } else {
        curr->branchsize = 1 + treeSize(curr->left) + treeSize(curr->right);
        return curr->branchsize;
    }
}

long treeHeight(node* curr)
{
    // calcola e memorizza la dimensione di ogni branch
    if(curr == NULL) {
        return 0;
    } else {
        long l1 = treeHeight(curr->left);
        long l2 = treeHeight(curr->right);
        return 1 + (l1 > l2 ? l1 : l2);
    }
}

node* costruiscisz(int i1, int i2, adt** linea, node* curr)
{
    // costruisci albero bilanciato da array di elementi ordinati
    // l' ordine e' uguale a quello di una ricerca binaria
    if(i1 >= i2) {
        return NULL;
    }
    int i3 = (i1 + i2) / 2;
    adt* ad = *(linea + i3);
    node* ret = createnode(ad, curr);
    ret->left = costruiscisz(i1, i3, linea, ret);
    ret->right = costruiscisz(i3 + 1, i2, linea, ret);
    ret->branchsize =
        1 + (ret->left == NULL ? 0 : ret->left->branchsize) + (ret->right == NULL ? 0 : ret->right->branchsize);
    return ret;
}

void pro(int i1, int i2, int indent)
{
    // simula come ricerca binaria
    // alg usato per costruire albero bilanciato
    if(i1 >= i2) {
        return;
    }
    int i3 = (i1 + i2) / 2;
    char* p = buf + indent;
    *p-- = '\0';
    while(p >= buf) {
        *p-- = ' ';
    }
    printf("%d\n", i3);
    pro(i1, i3, indent + 4);
    pro(i3 + 1, i2, indent + 4);
}

char* esempib[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "p", "q", "r", "s", "" };

node* bilancia(node* root)
{
    // crea prima lista piatta visitando l'albero,
    // poi ricrealo inserendo in modo da crealo bilanciato
    long cnt = root->branchsize; // oppure:  treeSize(root);
    long sz = sizeof(adt*) * cnt;
    adt** linea = malloc(sz);
    linearr(root, linea);
    node* ret = costruiscisz(0, cnt, linea, NULL);
    free(linea);
    return ret;
}

int testbinario()
{
    node* root = NULL;
    for(char** iniz = esempib; **iniz != '\0'; iniz++) {
        if(root == NULL) {
            root = insertsz(NULL, createadt(*iniz, iniz - esempib));
        } else {
            insertsz(root, createadt(*iniz, iniz - esempib));
        }
    }
    printf("SIZE %ld\n", treeSize(root));
    adelem* lin = linearizza(root, NULL);
    printf("lista doppia non circorae indietro\n");
    for(adelem* q = lin; q != NULL; q = q->prev) {
        printf("%s\n", tostr(q->el));
    }
    printf("Sbilanciato\n");
    printTree(root, 0);
    //   pro(0, 7, 0);
    root = bilancia(root);
    printf("Ora bilanciato\n");
    printTree(root, 0);
    testnaviga0(root);
    testnaviga1(root);
    testnaviga2(root);
    removeAdt(root, createadt("c", 2));
    removeAdt(root, createadt("d", 3));
    removeAdt(root, createadt("j", 9));
    // printTree(root, 0);
    testnaviga2(root);
    return 0;
}

int testbinariolist()
{
    node* root = NULL;
    char buf[24];
    adt* linea[SZ];
    for(int count = 0; count < SZ; count++) {
        sprintf(buf, "%d", count);
        linea[count] = createadt(buf, count);
    }
    root = costruiscisz(0, SZ, linea, NULL);
    //  return ret;//bilanciadaarray(linea, SZ);

    miotempo(NULL);
    //  treeSize(root);
    miotempo(" treesize 100000");
    //   printf("albero bilanciato size %ld\n", treeSize(root));
    miotempo(NULL);
    node* prova = elemat(root, 90000);
    miotempo(" binario navigo a el 90000");
    printf("trovo %s\n", tostr(prova->elem));
    miotempo(NULL);
    node* prova1 = elempos(root, 90017);
    miotempo("binario branch navigo a 90017");
    printf("trovo %s\n", tostr(prova1->elem));
    return 0;
}

int testbinarioinsertremove()
{

    char buf[24];
    adt* linea[SZ];
    for(int count = 0; count < SZ; count++) {
        sprintf(buf, "%d", count * 5);
        linea[count] = createadt(buf, count * 5);
    }
    miotempo(NULL);
    node* root = costruiscisz(0, SZ, linea, root);
    miotempo(" crea tree size 100000");
    miotempo(NULL);
    testnaviga2(root);
    miotempo(" naviga2 100000");
    miotempo(NULL);
    testnaviga3(root);
    miotempo(" naviga3 100000");
    miotempo(NULL);
    testnaviga4(root);
    miotempo(" naviga4 100000");
    miotempo(NULL);
    testnaviga5(root);
    miotempo(" naviga5 100000");

    printf("tressizestart %ld\n", treeSize(root));
    miotempo(NULL);
    for(int count = 0; count < SZ / 10; count++) {
        sprintf(buf, "%d", count + 2);
        insertsz(root, createadt(buf, count + 2));
    }
    miotempo(" insert tree 10000");
    printf("tressizedopoinsert %ld\n", treeSize(root));
    miotempo(NULL);
    for(int count = 0; count < SZ / 10; count++) {
        sprintf(buf, "%d", count + 2);
        removeAdt(root, createadt(buf, count + 2));
    }
    miotempo(" remove tree 10000");
    printf("tressize dopo remove %ld\n", treeSize(root));
    node* prova = elemat(root, 90000);
    miotempo(" binario navigo sequenziale a el 90000");
    printf("trovo %s\n", tostr(prova->elem));
    miotempo(NULL);
    node* prova1 = elempos(root, 90000);
    miotempo("binario branch navigo binarion a el 90000");
    printf("trovo %s\n", tostr(prova1->elem));
    return 0;
}

int testbinarioinsertrandom()
{
    char buf[24];
    adt* linea[SZ];
    srand(1000);
    for(int count = 0; count < SZ; count++) {
        int cur = rand() % 1000000;
        sprintf(buf, "%d", cur);
        linea[count] = createadt(buf, cur);
    }
    node* root = NULL;
    miotempo(NULL);
    adt** soglia = linea + SZ - 20001;
    for(adt** iniz = linea + SZ - 1; iniz > linea; iniz--) {
        if(root == NULL) {
            root = insertsz(NULL, *iniz);
        } else {
            insertsz(root, *iniz);
        }
        if(0 && iniz == soglia) {
            // bilancia dopo 20K elementi
            root = bilancia(root);
        }
    }
    printf("TREEHEIGHT prima %ld\n", treeHeight(root));
    root = bilancia(root);
    printf("TREEHEIGHT dopo %ld\n", treeHeight(root));
    // prova a reinserire i nodi, ovviamente non succedera' NULLA
    // serve a vedere quanto ci va a cercarli
    for(int aa = 0; aa < 10; aa++)
        for(adt** iniz = linea + SZ - 1; iniz >= linea; iniz--) {
            insertsz(root, *iniz);
        }
    miotempo(" crea tree random vero bilanciato 100000");
    printf("TREESIZE %ld\n", treeSize(root));
    printf("TREEHEIGHT dopo %ld\n", treeHeight(root));
    checkTree(root);
    return 0;
}