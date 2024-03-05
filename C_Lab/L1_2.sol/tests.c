#include "potenze.h"
#include "potenzestart.h"

#include <stdio.h>

int test_in[] = { 0, 1, 10, -1, 1234567890, 40000, 400000 };
int test_out[] = { 0, 1, 100, 1, -1, 1600000000, -1 };
char* test_comments[] = { "test1", "t2", "t3", "t4", "t5", "t6", "t7" };
#define SIZE (sizeof(test_in) / sizeof(test_in[0]))
int test_failures[SIZE];

int test_in_p1[] = { 3, 3, 3, -1, -1, 0, -1 };
int test_in_p2[] = { 4, 0, 1, 1, 0, 0, 2 };
int test_out_r3[] = { 81, 1, 3, -1, 1, 0, 1 };
#define SIZE1 (sizeof(test_in_p1) / sizeof(test_in_p1[0]))
int test_failures1[SIZE1];

int test1()
{
    int fail = 0;
    for(int i = 0; i < SIZE1; i++) {
        printf(" test number %d(%s), input = %d, output=%d", i, test_comments[i], test_in[i], test_out[i]);
        int res = quadratoOK2(test_in[i]);
        if(res != test_out[i]) {
            printf(" Fail  res= %d\n", res);
            test_failures[i] = 1;
            fail++;
        } else {
            printf(" OK \n");
        }
    }
    printf("\npercentage failures = %d%%\n", (int)(100.0 * fail / SIZE1));
    return 0;
}

int test2()
{
    int fail = 0;
    for(int i = 0; i < SIZE1; i++) {
        printf(" test number %d, input = %d,%d; output=%d", i, test_in_p1[i], test_in_p2[i], test_out_r3[i]);
        int res = potenza(test_in_p1[i], test_in_p2[i]);
        if(res != test_out_r3[i]) {
            printf(" Fail  res= %d\n", res);
            test_failures[i] = 1;
            fail++;
        } else {
            printf(" OK \n");
        }
    }
    printf("\npercentage failures = %d%%\n", (int)(100.0 * fail / SIZE));
    /*  printf("potenza %d %d %d\n", 3, 4, potenza(3, 4));
      printf("potenza %d %d %d\n", 3, 0, potenza(3, 0));
      printf("potenza %d %d %d\n", 3, 1, potenza(3, 1));
      printf("potenza %d %d %d\n", -1, 1, potenza(-1, 1));
      printf("potenza %d %d %d\n", -1, 0, potenza(-1, 0));
      printf("potenza %d %d %d\n", 0, 0, potenza(0, 0));
      printf("potenza %d %d %d\n", -1, 2, potenza(-1, 2));
  */
    return 0;
}
