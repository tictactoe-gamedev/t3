#include "helpers.h"
#include "adt.h"

T3_Queue *T3_Queue_Init() {
    T3_HELPER_MALLOC_SAFE(T3_Queue, queue);
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
    T3_HELPER_ASSERT(queue->Count != 0, "Nothing to dequeue!");

    T3_Node *current = queue->Head;
    queue->Head = queue->Head->Next;
    if (queue->Count == 2) {
        queue->Tail = NULL;
    }

    queue->Count--;

    return current;
}

void T3_Queue_Destroy(T3_Queue *queue) {
    int i;
    for (i = 0; i < queue->Count; ++i) {
        T3_Node *removed = T3_Queue_Dequeue(queue);
        T3_Node_Destroy(removed);
    }
    free(queue);
}

void T3_Queue_Log_Int(T3_Queue *queue) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    int i = 0;
    T3_Node *node = queue->Head;
    while (node != NULL) {
        T3_HELPER_LOG(Info, "[%d]: [%d]", i, *(int *) node->Data);
        node = node->Next;
        i++;
    }
#endif
}

void T3_Queue_Test() {
#if CONFIG_BUILD_TYPE == DEVELOPMENT

    T3_Queue *queue = T3_Queue_Init();
    T3_Queue_Enqueue(queue, T3_Node_Init_Int(1));
    T3_Queue_Enqueue(queue, T3_Node_Init_Int(2));
    T3_Queue_Enqueue(queue, T3_Node_Init_Int(3));
    T3_Queue_Log_Int(queue);
    T3_Node *node = T3_Queue_Dequeue(queue);
    T3_Queue_Log_Int(queue);
    T3_Queue_Destroy(queue);

#endif
}




