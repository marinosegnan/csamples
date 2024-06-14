#include "cha.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct listNode ListNode, *ListNodePtr;
struct listNode {
   char data;
   ListNodePtr next;
};

struct charQueue {
    ListNodePtr front; /* Punta al primo nodo della lista, che contiene l'elemento in testa alla coda, se la coda è vuota vale NULL */
    ListNodePtr rear; /* Punta all'ultimo nodo della lista, che contiene l'elemento in fondo alla coda, se la coda è vuota vale NULL */
    int size;
    /* aggiungere eventuali altre variabili per ottenere una implementazione più efficiente */
};

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    CharQueueADT queue = (CharQueueADT)malloc(sizeof(struct charQueue));
    queue -> front = NULL;
    queue -> rear = NULL;
    queue -> size = 0;
    return queue;
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    free(*pq);
    *pq = NULL;
}

/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    if (q == NULL) {
        return 0; // Fallimento: la coda è NULL
    }

    // Allocare un nuovo nodo
    ListNodePtr Nuovo = (ListNodePtr)malloc(sizeof(ListNode));
    if (Nuovo == NULL) {
        return 0; // Fallimento: memoria non disponibile
    }

    // Inizializzare il nuovo nodo
    Nuovo->data = e;
    Nuovo->next = NULL;

    // Aggiungere il nuovo nodo alla fine della coda
    if (q->rear == NULL) {
        // La coda è vuota
        q-> front = Nuovo;
        q-> rear = Nuovo;
        q-> size++;
    } else {
        // La coda non è vuota
        q->rear->next = Nuovo;
        q->rear = Nuovo;
        q-> size++;
    }
    return 1; // Successo
}

/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
    if(q == NULL || q -> front == NULL)
    {
    printf("SZN %d\n",q->size);
        return 0;
    }
    else
    {
        *res = q -> front -> data;
        q -> front  = q -> front -> next;
        q -> size--;
        if (q->size ==0){
            q->rear = NULL;
        }
    }
    printf("SZ %d\n",q->size);
    return *res;
}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if(q -> front == NULL || q -> rear == NULL)
    {
        return true;
    }
    else return false;
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    //printf("%d\n questo e il size : ", q -> size);
    return q -> size;
}

/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res) {
    ListNodePtr tmp = q -> front;
    while(tmp != NULL)
    {
        if(tmp -> data == *res)
        {
            return position;
        }
        else
        {
            tmp = tmp -> next;
            position ++;
        }
    }
    return false;
}
 int passed = 1;
void prova(){
   
    char res;
    int ret;
    CharQueueADT q = mkQueue();
    ret = size(q);
    printf("%d\n",ret);
    if(ret != 0) { passed = 0; return; }
    ret = enqueue(q,'w');
    ret = size(q);
    printf("%d\n",ret);
    if(ret != 1) { passed = 0; return; }
    ret = dequeue(q,&res);
    ret = size(q);
    printf("%d\n",ret);
    if(ret != 0) { passed = 0; return; }
    ret = enqueue(q,'a');
    ret = size(q);
    printf("%d\n",ret);
    ret = enqueue(q,'b');
     ret = size(q);
    printf("%d\n",ret);
    ret = dequeue(q,&res);
     ret = size(q);
    printf("%d\n",ret);
    ret = enqueue(q,'c');
    ret = size(q);
    printf("%d\n",ret);
    if(ret != 2) { passed = 0; return; }
    dsQueue(&q);
    return;
}
int main (int argc, char *argv[]){
prova();
printf("%d\n",passed);
}

