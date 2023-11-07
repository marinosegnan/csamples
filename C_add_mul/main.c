#include <addmul.h>
#include <addmul30.h>
#include <assert.h>
#include <debug.h>
#include <gmp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tempi.h>
// digits e' la meta' scarsa di cifre di un long
// cosi che la moltiplicazione di due numeri di massimo DIGITS non da' overflow
// per la somma possiamo arrivare a un difit in meno del massimo
// per 64 bit digits abbiamo 19 cifre quindi:

char* str3 = "23456781234";
char* str4 = "876543218765";

void para(int e1, int e2)
{

    printf("\n");
    char* nu1 = molti(str3, e1);
    char* nu2 = molti(str4, e2);
    arr* op1 = create(nu1, 0, 0, 10,DIGITS);
    arr* op2 = create(nu2, 0, 0, 10,DIGITS);
    miotempo(NULL);
    arr* result = mul3(op1, op2);
    miotempo("\nmul3 9 /18cifre ");
 //   printf("result = %s\n", tostr(result));
    miotempo(NULL);
    result = mul(op1, op2);
    miotempo("\nmulast 9 con sum ");

    
 //    printf("result = %s\n", tostr(result));
    mpz_t g1, g2, g3;
    mpz_init(g1);
    mpz_set_ui(g1, 0);
    mpz_init(g2);
    mpz_set_ui(g2, 0);
    mpz_init(g3);
    mpz_set_ui(g3, 0);

    /* 2. Parse the input string as a base 10 number */
    int flag = mpz_set_str(g1, nu1, 10);
    assert(flag == 0); /* If flag is not 0 then the operation failed */
    flag = mpz_set_str(g2, nu2, 10);
    assert(flag == 0);
    miotempo(NULL);
    mpz_mul(g3, g1, g2);
    miotempo("\nGNU");
    arr* n1 = strtobasebits(nu1, 30, DIGITS);
 //   dumpi(n1);
 //  arr* vv =  tobase(n1,10,9);
 //  printf("BASE2 %s\n",tostr(vv));
    arr* n2 = strtobasebits(nu2, 30, DIGITS);
    miotempo(NULL);
    result = mulbase2(n1, n2);
    miotempo("\nmulbase2");
  //  dumpi(result);
    miotempo(NULL);
    result = muladdbase2(n1, n2);
 //   dumpi(result);
   //  arr* vv =  tobase(result,10,9);
   // printf("BASE2%s\n",tostr(vv));
    miotempo("\nmuladdbase2");
}

void dok(int e1, int e2)
{
    char* nu1 = molti(str3, e1);
    char* nu2 = molti(str4, e2);
    initzero();
    arr* op1 = create(nu1, 0, 0, 10,DIGITS);
    arr* op2 = create(nu2, 0, 0, 10,DIGITS);
    miotempo(NULL);
    arr* result = karat(op1, op2);
    miotempo("\nkarat 9 con crea ");
}

void prove()
{
  /*  dok(19, 21);
    dok(199, 211);
    para(19, 21);
    para(199, 211);
  */  
  //  arr* nu = strtobasebits(molti(str3,100), 30, DIGITS);
 //  arr* vv =  tobase(nu,10,9);
 //   printf("%s\n",tostr(vv));
      
    arr* nu = strtobasebits(molti("123456",1), 4, DIGITS);
    printf("provo\n");
    dumpi(nu);
   arr* vv =  tobase(nu,10,1);
     printf("ottengo\n");
     dumpi(vv);
}

int main() { prove();return 0; }
