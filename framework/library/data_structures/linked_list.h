#ifndef T3_LINKED_LIST_H
#define T3_LINKED_LIST_H

#include <cstddef>
#include <cstdlib>
#include "node.h"

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

T3_LinkedList *T3_LinkedList_Init();
T3_LinkedListDouble *T3_LinkedListDouble_Init();

void T3_LinkedList_AddToHead(T3_LinkedList *list, T3_Node *node);
void T3_LinkedListDouble_AddToHead(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedList_AddToTail(T3_LinkedList *list, T3_Node *node);
void T3_LinkedListDouble_AddToTail(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedList_AddToIndex(T3_LinkedList *list, T3_Node *node, uint index);
void T3_LinkedListDouble_AddToIndex(T3_LinkedListDouble *list, T3_NodeDouble *node, uint index);

void T3_LinkedList_AddNode(T3_LinkedList *list, T3_Node *node, uint index);
void T3_LinkedListDouble_AddNode(T3_LinkedListDouble *list, T3_NodeDouble *node, uint index);

T3_Node *T3_LinkedList_GetNode(T3_LinkedList *list, uint index);
T3_NodeDouble *T3_LinkedListDouble_GetNode(T3_LinkedListDouble *list, uint index);

uint T3_LinkedList_FindIndexOf(T3_LinkedList *list, T3_Node *node);
uint T3_LinkedListDouble_FindIndexOf(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedList_Remove(T3_LinkedList *list, T3_Node *node);
void T3_LinkedListDouble_Remove(T3_LinkedListDouble *list, T3_NodeDouble *node);

T3_Node *T3_LinkedList_RemoveAt(T3_LinkedList *list, uint index);
T3_NodeDouble *T3_LinkedListDouble_RemoveAt(T3_LinkedListDouble *list, uint index);

void T3_LinkedList_DestroyNode(T3_LinkedList *list, T3_Node *node);
void T3_LinkedListDouble_DestroyNode(T3_LinkedListDouble *list, T3_NodeDouble *node);

void T3_LinkedList_DestroyNodeAt(T3_LinkedList *list, uint index);
void T3_LinkedListDouble_DestroyNodeAt(T3_LinkedListDouble *list, uint index);

void T3_LinkedList_Destroy(T3_LinkedList *list);
void T3_LinkedListDouble_Destroy(T3_LinkedListDouble *list);

void T3_LinkedList_Test();
void T3_LinkedListDouble_Test();

#endif //T3_LINKED_LIST_H
