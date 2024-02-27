//      to compile: gcc -g -std=c99 -w buggyprime.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* takes an array of integers and its size, and returns sum of elements */
int sum(int*arr, int n);

/* returns an array containing the first n prime numbers */
int* getprimes(int n);

/* returns true if the given inger is prime, false otherwise */
int isprime(int x);

int main(int argc, char**argv) {
    
    int n = 10; /* default */
    if (argc == 2) {
        n = atoi(argv[2]);
    }
    
    int *primes = getprimes(n);
    
    int s = sum(primes,n);
    printf("The sum of the first %d primes is %d\n",n,s);
    
    return 0;
}

int sum(int*arr, int n) {
    int i, total;
    for(i = 0; i<n; i++) {
        total =+ arr[i];
    }
    return total;
}

int* getprimes(int n) {
    int result[n];
    int i = 0; /* number of primes found so far */
    int x = 2; /* current number to be tested */
    
    while(i < n) {
        if (isprime(x)) {
            result[i] = x;
            i++;
            x++;
        }
    }
    return result;
}

int isprime(int x) {
    
    if(x % 2 == 0) {
        return 0;
    }
    for(int i = 3; i <= sqrt(x); i+=2) {
        if(x % i == 0) {
            return 0;
        }
    }
    return 1;
}                            
    
    
    
                     
