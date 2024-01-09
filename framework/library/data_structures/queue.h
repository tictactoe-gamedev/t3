#ifndef T3_QUEUE_H
#define T3_QUEUE_H

#include <cstdlib>
#include "node.h"

typedef struct T3_Queue {
    T3_Node *Head;
    T3_Node *Tail;
    uint Count; 
} T3_Queue;

T3_Queue *T3_Queue_Init();

void T3_Queue_Enqueue(T3_Queue *queue, T3_Node *node);

T3_Node *T3_Queue_Dequeue(T3_Queue *queue);

void T3_Queue_Destroy(T3_Queue* queue);

void T3_Queue_Test();

#endif //T3_QUEUE_H
