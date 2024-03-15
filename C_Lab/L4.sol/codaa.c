#include "coda.h"

#include <stdlib.h>

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