typedef struct charQueue* CharQueueADT;

CharQueueADT mkQueue();
void dsQueue(CharQueueADT* pq);
void enqueue(CharQueueADT q, char e);
int dequeue(CharQueueADT q);
int isEmpty(CharQueueADT q);
int size(CharQueueADT q);
char peek(CharQueueADT q, int position);
