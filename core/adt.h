#ifndef T3_ADT_H
#define T3_ADT_H

#include "core/t3-types.h"

typedef struct T3_Node T3_Node;
typedef struct T3_NodeDouble T3_NodeDouble;

struct T3_Node {
    void *Data;
    T3_Node *Next;
};

struct T3_NodeDouble {
    void *Data;
    T3_NodeDouble *Prev;
    T3_NodeDouble *Next;
};

typedef struct T3_LinkedList {
    T3_Node *Head;
    T3_Node *Tail;
    uint Count;
} T3_LinkedList;

typedef struct T3_LinkedListDouble {
    T3_NodeDouble *Head;
    T3_NodeDouble *Tail;
    uint Count;
} T3_LinkedListDouble;

typedef struct T3_List {
    void **Array;
    size_t Capacity;
    size_t Size;
    size_t *_removedIndices;
    size_t _removedIndicesSize;
    size_t _removedIndicesCapacity;
} T3_List;

typedef struct T3_Queue {
    T3_Node *Head;
    T3_Node *Tail;
    size_t Count;
} T3_Queue;

typedef struct T3_Stack {
    T3_Node *Top;
    size_t Count;
} T3_Stack;

/** ------------------------------- NODE ----------------------------------- */

T3_Node *T3_Node_Init(void *data);

T3_Node *T3_Node_Init_Int(int data);

T3_Node *T3_Node_Init_Float(float data);

void T3_Node_Destroy(T3_Node *node);

/** ------------------------------- NODE DOUBLE ----------------------------------- */

T3_NodeDouble *T3_NodeDouble_Init(void *data);

T3_NodeDouble *T3_NodeDouble_Init_Int(int data);

T3_NodeDouble *T3_NodeDouble_Init_Float(float data);

void T3_NodeDouble_Destroy(T3_NodeDouble *node);

/** ------------------------------- LINKED LIST ----------------------------------- */

T3_LinkedList *T3_LinkedList_Init();

/** Add node without considering if its head, tail or between. Secure but relatively slow */
void T3_LinkedList_AddNode(T3_LinkedList *list, T3_Node *node, size_t index);

void T3_LinkedList_AddToHead(T3_LinkedList *list, T3_Node *node);

void T3_LinkedList_AddToTail(T3_LinkedList *list, T3_Node *node);

/** Use it ONLY if you know the position is not head or tail */
void T3_LinkedList_AddToIndex(T3_LinkedList *list, T3_Node *node, size_t index);

T3_Node *T3_LinkedList_GetNode(T3_LinkedList *list, size_t index);

void T3_LinkedList_Remove(T3_LinkedList *list, T3_Node *node);

T3_Node *T3_LinkedList_RemoveAt(T3_LinkedList *list, size_t index);

size_t T3_LinkedList_FindIndexOf(T3_LinkedList *list, T3_Node *node);

void T3_LinkedList_Destroy(T3_LinkedList *list);

void T3_LinkedList_DestroyNode(T3_LinkedList *list, T3_Node *node);

void T3_LinkedList_DestroyNodeAt(T3_LinkedList *list, size_t index);

void T3_LinkedList_Log_Int(T3_LinkedList *list);

void T3_LinkedList_Test();

/** ------------------------------- LINKED LIST DOUBLE ----------------------------------- */

T3_LinkedListDouble *T3_LinkedListDouble_Init();

/** Add node without considering if its head, tail or between. Secure but relatively slow */
void T3_LinkedListDouble_AddNode(T3_LinkedListDouble *list, T3_NodeDouble *node, size_t index);

void T3_LinkedListDouble_AddToHead(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedListDouble_AddToTail(T3_LinkedListDouble *list, T3_NodeDouble *node);

/** Use it ONLY if you know the position is not head or tail */
void T3_LinkedListDouble_AddToIndex(T3_LinkedListDouble *list, T3_NodeDouble *node, size_t index);

T3_NodeDouble *T3_LinkedListDouble_GetNode(T3_LinkedListDouble *list, size_t index);

void T3_LinkedListDouble_Remove(T3_LinkedListDouble *list, T3_NodeDouble *node);

T3_NodeDouble *T3_LinkedListDouble_RemoveAt(T3_LinkedListDouble *list, size_t index);

size_t T3_LinkedListDouble_FindIndexOf(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedListDouble_Destroy(T3_LinkedListDouble *list);

void T3_LinkedListDouble_DestroyNode(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedListDouble_DestroyNodeAt(T3_LinkedListDouble *list, size_t index);

void T3_LinkedListDouble_Log_Int(T3_LinkedListDouble *list);

void T3_LinkedListDouble_Test();

/** ------------------------------- LIST ----------------------------------- */

/** Initialize a list with initialCapacity and initialCapacity/2 cache for removed items */
T3_List *T3_List_Init(size_t initialCapacity);

/** Checks if there's a capacity overflow. If so, increase the capacity x 2 */
void T3_List_AddSafe(T3_List *list, void *element);

void T3_List_Add(T3_List *list, void *element);

void T3_List_Remove(T3_List *list, void *element);

/**  Remove item from list. Also checks if the removed item cache is overflowed. Flushes the cache if necessary */
void T3_List_RemoveSafe(T3_List *list, void *element);

void *T3_List_RemoveAt(T3_List *list, size_t index);

void *T3_List_RemoveAtSafe(T3_List *list, size_t index);

void T3_List_Resize(T3_List *list, size_t newCapacity);

/** Changes the capacity of cached elements which are removed from the list */
void T3_List_ResizeCache(T3_List *list, size_t newCapacity);

void *T3_List_Get(T3_List *list, size_t index);

int T3_List_FindIndexOf(T3_List *list, void *element);

void T3_List_Set(T3_List *list, size_t index, void *element);

/** Cleans the removed elements cache. It's automatically cleaned when the removed item count reaches the capacity. */
void T3_List_CleanCache(T3_List *list);

void T3_List_Destroy(T3_List *list);

void T3_List_Test();

/** ------------------------------- QUEUE ----------------------------------- */

T3_Queue *T3_Queue_Init();

void T3_Queue_Enqueue(T3_Queue *queue, T3_Node *node);

T3_Node *T3_Queue_Dequeue(T3_Queue *queue);

void T3_Queue_Destroy(T3_Queue *queue);

void T3_Queue_Log_Int(T3_Queue *queue);

void T3_Queue_Test();

/** ------------------------------- STACK ----------------------------------- */

T3_Stack *T3_Stack_Init();

void T3_Stack_Push(T3_Stack *stack, T3_Node *node);

T3_Node *T3_Stack_Pop(T3_Stack *stack);

void T3_Stack_Destroy(T3_Stack *stack);

void T3_Stack_Log_Int(T3_Stack *queue);

void T3_Stack_Test();

#endif //T3_ADT_H
