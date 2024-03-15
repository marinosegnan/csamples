#include "coda.h"

#include <stdlib.h>

typedef struct listNode {
    char data;
    struct listNode* next;
} ListNode, *ListNodePtr;

typedef struct charQueue {
    ListNodePtr front;
    ListNodePtr rear;
    int size;
} CharQueue, *CharQueueADT;

CharQueueADT mkQueue()
{
    CharQueueADT ret = malloc(sizeof(CharQueue));
    ret->front = NULL;
    ret->rear = NULL;
    ret->size = 0;
    return ret;
}

void dsQueue(CharQueueADT* pq)
{
    free(*pq);
    *pq = NULL;
}

int dequeue(CharQueueADT q)
{
    if(q->front == NULL) {
        return -1;
    } else {
        ListNodePtr remo = q->front;
        char ret = remo->data;
        q->front = remo->next;
        free(remo);
        q->size--;
        return ret;
    }
}

void enqueue(CharQueueADT q, char e)
{
    ListNodePtr inse = malloc(sizeof(ListNode));
    inse->data = e;
    inse->next = NULL;
    if(q->rear == NULL) {
        q->front = q->rear = inse;
    } else {
        q->rear->next = inse;
        q->rear = inse;
    }
    q->size++;
}

int isEmpty(CharQueueADT q) { return q->size == 0; }
int size(CharQueueADT q) { return q->size; }
char peek(CharQueueADT q, int position)
{
    if(q->front == NULL) {
        return -1;
    } else {
        return q->front->data;
    }
}