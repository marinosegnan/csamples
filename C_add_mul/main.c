#include <assert.h>
#include <debug.h>
#include <gmp.h>
#include <includere.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <tempi.h>

// digits e' la meta' scarsa di cifre di un long
// cosi che la moltiplicazione di due numeri di massimo DIGITS non da' overflow
// per la somma possiamo arrivare a un difit in meno del massimo
// per 64 bit digits abbiamo 19 cifre quindi:

char* str3 = "23456781234";
char* str4 = "876543218765";

void test(char* s1, int pow1, char* s2, int pow2, int testnum)
{
    long n1 = atol(s1) * pow(10, pow1);
    long n2 = atol(s2) * pow(10, pow2);
    long n3 = n1 + n2;
    char buf[20];
    sprintf(buf, "%ld", n3);
    arr* op1 = create(s1, 0, pow1, 10, DIGITS);
    arr* op2 = create(s2, 0, pow2, 10, DIGITS);
    arr* r1 = sumsimpleC(op1, op2);
    char* res1 = tostr(r1);
    arr* r2 = sumsimpleC(op2, op1);
    char* res2 = tostr(r2);
    if(strcmp(res1, buf) != 0) {
        printf("m n mio uff  %s %s %s %s (%d)\n", tostr(op1), tostr(op2), res1, buf, testnum);
    }
    if(strcmp(res2, buf) != 0) {
        printf("m n mio uff  %s %s %s %s (%d)\n", tostr(op2), tostr(op1), res2, buf, testnum);
    }
    op1 = create(s1, 0, pow1, 10, DIGITS);
    op2 = create(s2, 0, pow2, 10, DIGITS);
    char* v3 = tostr(op1);
    char* v4 = tostr(op2);
    arr* op3 = sumsimple(op1, op2);
    char* res3 = tostr(op3);
    if(strcmp(res3, buf) != 0) {
        printf("m n mio SIMPLE uff  %s-%s-%s-%s-(%d)\n", v3, v4, res3, buf, testnum);
    }
}

arr* dok(int e1, int e2)
{
    char* nu1 = molti(str3, e1);
    char* nu2 = molti(str4, e2);
    arr* op1 = create(nu1, 0, 0, 10, DIGITS);
    arr* op2 = create(nu2, 0, 0, 10, DIGITS);
    miotempo(NULL);
    arr* result = karat(op1, op2);
    miotempo("\nkarat 9 con crea ");
    return result;
}

arr* para(int e1, int e2)
{
    printf("\n");
    char* nu1 = molti(str3, e1);
    char* nu2 = molti(str4, e2);
    arr* op1 = create(nu1, 0, 0, 10, DIGITS);
    arr* op2 = create(nu2, 0, 0, 10, DIGITS);
    miotempo(NULL);
    arr* result18 = mul3(op1, op2);
    miotempo("\nmul3 9 /18cifre ");
    //   printf("result18 = %s\n", tostr(result18));
    miotempo(NULL);
    arr* result9 = mul(op1, op2);
    miotempo("\nmulast 9 con sum ");
    //   printf("result9 = %s\n", tostr(result9));
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
    arr* n2 = strtobasebits(nu2, 30, DIGITS);
    miotempo(NULL);
    arr* result2 = muladdbase2(n1, n2);
    //   printf("result2 %s\n", tostr(result2));
    miotempo(NULL);
    arr* result3 = mulbase2(n1, n2);
    miotempo("mulbase2");
    //   printf("res mulbase2 %s\n", tostr(result3));
    verify(result2, result3);
    verify(result2, result9);
    verify(result2, result18);
    return result9;
}

void runtest()
{

    if(DIGITS != 1) {
        printf("test non eseguiti, validi solo con DIGITS ==1\n\n");
        return;
    }
    test("120000000000", 0, "13", 10, 1);
    test("12", 10, "13", 0, 2);
    test("12", 10, "13", 3, 3);
    test("12112", 5, "13", 3, 6);
    test("12", 7, "13", 6, 11);
    test("12", 0, "13", 3, 4);
    test("121", 0, "13", 3, 5);
    test("12112", 5, "13", 5, 7);
    test("12112", 2, "13", 5, 8);
    test("12", 10, "13", 12, 9);
    test("12", 1, "13", 3, 10);

    test("123456", 0, "0", 4, 12);
    test("123456", 0, "0", 0, 13);
    printf("Fine test\n");
}

int main()
{
    arr* nu = strtobasebits(molti("123456",1),4,DIGITS);
    dumpi(nu);
    arr*vv=cambiabase(nu,10,1);
    dumpi(vv);
    runtest();

    arr* k2 = dok(199, 211);
    statis();
    //   printf("karat res %s\n", tostr(k2));
    arr* m4 = para(199, 211);
    //   printf("karat res %s\n", tostr(m4));
    verify(m4, k2);
    return 0;
}