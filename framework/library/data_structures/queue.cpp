#include "queue.h"
#include "helper/memory.h"
#include "config/game-config.h"

#define Next Ptr1

T3_Queue *T3_Queue_Init() {
    T3_MallocSafe(T3_Queue, queue)
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
}

T3_Node *T3_Queue_Dequeue(T3_Queue *queue) {
    T3_Assert(queue->Count == 0, "Nothing to dequeue!")

    T3_Node *current = queue->Head;
    queue->Head = queue->Head->Next;
    if (queue->Count == 2) {
        queue->Tail = NULL;
    }

    queue->Count--;

    return current;
}

void T3_Queue_Destroy(T3_Queue *queue) {
    for (int i = 0; i < queue->Count; ++i) {
        T3_Node * removed = T3_Queue_Dequeue(queue);
        T3_Node_Destroy(removed);
    }
    free(queue);
}

void T3_Queue_Test() {
#ifdef GAME_RELEASE
    #if GAME_RELEASE == DEVELOPMENT

    T3_Queue * queue = T3_Queue_Init();
    T3_Queue_Enqueue(queue, T3_Node_Init(1));
    T3_Queue_Enqueue(queue, T3_Node_Init(2));
    T3_Queue_Enqueue(queue, T3_Node_Init(3));
    T3_Log(LOG_LEVEL_INFO,queue);
    T3_Node* node = T3_Queue_Dequeue(queue);
    T3_Log(LOG_LEVEL_INFO,queue);
    T3_Queue_Destroy(queue);    
    
    #endif
#endif
}




