#include "coda.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 8

struct charQueue {
    int capacity;
    char* a;
    int size;
    int rear;
    int front;
};

CharQueueADT mkQueue()
{
    CharQueueADT ret = malloc(sizeof(struct charQueue));
    ret->capacity = INITIAL_CAPACITY;
    ret->a = malloc(ret->capacity * sizeof(char));
    ret->size = 0;
    ret->front = ret->rear = 0;
    return ret;
}

void dsQueue(CharQueueADT* pq)
{
    // non libero tutta la coda!
    free((*pq)->a);
    free(*pq);
    *pq = NULL;
}

int dequeue(CharQueueADT q)
{
    int ret = -1;
    if(q->size > 0) {
        ret = q->a[q->front];
        q->front = (q->front + 1) % q->capacity;
        q->size--;
        if(q->size < q->capacity / 4) { // 4 e' una costante a piacere
        // rimpicciolisci
            char* nuovo = malloc((q->capacity / 2) * sizeof(char));
        /*    for(int j = 0, k = q->front; j < q->size; j++) {
              // piu' lento
                nuovo[j] = q->a[k];
                k = (k + 1) % q->capacity;
            }*/
            if (q->front <= q->rear){
                memcpy(nuovo,q->a+q->front,q->rear-q->front);
            } else{
                memcpy(nuovo,q->a+q->front,q->capacity-q->front);
                memcpy(nuovo+q->capacity-q->front,q->a,q->rear);
            }
            q->front = 0;
            q->rear = q->size;
            free(q->a);
            q->a = nuovo;
            q->capacity /= 2;
        }
    }
    return ret;
}

void enqueue(CharQueueADT q, char e)
{
    if(q->size >= q->capacity) {
        q->capacity *= 2;
        q->a = realloc(q->a, q->capacity * sizeof(char));
    }
    q->a[q->rear] = e;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

int isEmpty(CharQueueADT q) { return q->size == 0; }
int size(CharQueueADT q) { return q->size; }
char peek(CharQueueADT q, int position) { return q->size > 0 ? q->a[q->front] : -1; }