#include <SDL_log.h>
#include <SDL_assert.h>
#include "t3-helpers.h"
#include "t3-abstract-data-types.h"

T3_Queue *T3_Queue_Init(void) {
    T3_Queue *queue = T3_Helper_Malloc_Safe(sizeof *queue, T3_FILE, T3_LINE);
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
    T3_Node *current;
    SDL_assert(queue->Count != 0);
    
    current = queue->Head;
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
        SDL_Log("%s[%d]: [%d]->[%d]", T3_FILE, T3_LINE, i, *(int *) node->Data);
        node = node->Next;
        i++;
    }
#endif
}

void T3_Queue_Test(void) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    T3_Node *node;
    T3_Queue *queue = T3_Queue_Init();
    T3_Queue_Enqueue(queue, T3_Node_Init_Int(1));
    T3_Queue_Enqueue(queue, T3_Node_Init_Int(2));
    T3_Queue_Enqueue(queue, T3_Node_Init_Int(3));
    T3_Queue_Log_Int(queue);
    node = T3_Queue_Dequeue(queue);
    T3_Queue_Log_Int(queue);
    T3_Queue_Destroy(queue);

#endif
}
