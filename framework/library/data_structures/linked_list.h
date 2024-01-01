#ifndef T3_LINKED_LIST_H
#define T3_LINKED_LIST_H

#include <cstddef>
#include <cstdlib>
#include "node.h"

typedef struct LinkedList{
    T3_Node* Head;
    T3_Node* Tail;
    uint Count;
}LinkedList;

typedef struct LinkedListDouble{
    T3_NodeDouble* Head;
    T3_NodeDouble* Tail;
    uint  Count;
}LinkedListDouble;

LinkedList* LinkedList_Init();
LinkedListDouble* LinkedListDouble_Init();

void LinkedList_AddNode(LinkedList* list, T3_Node* node, uint index);
void LinkedListDouble_AddNode(LinkedListDouble* list, T3_NodeDouble* node, uint index);

T3_Node* LinkedList_GetNode(LinkedList* list, uint index);
T3_NodeDouble* LinkedListDouble_GetNode(LinkedListDouble* list, uint index);

void LinkedList_Remove(LinkedList* list, T3_Node* node);
void LinkedListDouble_Remove(LinkedListDouble* list, T3_NodeDouble* node);

void LinkedList_RemoveAt(LinkedList* list, uint index);
void LinkedListDouble_RemoveAt(LinkedListDouble* list, uint index);

void LinkedList_DestroyNode(LinkedList* list, T3_Node* node);
void LinkedListDouble_DestroyNode(LinkedListDouble* list, T3_NodeDouble * node);

void LinkedList_DestroyNodeAt(LinkedList* list, uint index);
void LinkedListDouble_DestroyNodeAt(LinkedListDouble* list, uint index);


#endif //T3_LINKED_LIST_H
