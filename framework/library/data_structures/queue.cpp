#include "queue.h"
#include "helper/memory.h"

#define Next Ptr1


T3_Queue *T3_QueueInit(bool isCircular) {
    T3_MallocSafe(T3_Queue, queue)
    queue->IsCircular = isCircular;
    queue->Head = NULL;
    queue->Tail = NULL;
    queue->Count = 0;
    return queue;
}

void T3_Queue_Enqueue(T3_Queue *queue, T3_Node *node) {
    if (queue->Count == 0) {
        queue->Head = node;
    } else if (queue->Count == 1) {
        queue->Tail = node;
        queue->Head->Next = queue->Tail;
    } else {
        queue->Tail->Next = node;
        queue->Tail = node;
    }

    queue->Count++;

    if (queue->IsCircular) {
        node->Next = queue->Head;
    }
}

T3_Node *T3_Queue_Dequeue(T3_Queue *queue) {
    T3_Assert(queue->Count == 0, "Nothing to dequeue!")

    T3_Node *current = queue->Head;
    queue->Head = queue->Head->Next;
    if (queue->Count == 2) {
        queue->Tail = NULL;
    }

    queue->Count--;

    if (queue->IsCircular && queue->Count > 0) {
        if (queue->Count == 1) {
            queue->Head->Next = queue->Head;
        } else {
            queue->Tail->Next = queue->Head;
        }
    }

    return current;
}


