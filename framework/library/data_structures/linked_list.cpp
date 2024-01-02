#include "linked_list.h"
#include "helper/memory.h"
#include "helper/logging.h"

#define Next Ptr1
#define Prev Ptr2

LinkedList *LinkedList_Init() {
    T3_MallocSecure(LinkedList, list);
    list->Head = NULL;
    list->Tail = NULL;
    list->Count = 0;
    return list;
}

LinkedListDouble *LinkedListDouble_Init() {
    T3_MallocSecure(LinkedListDouble, list);
    list->Head = NULL;
    list->Tail = NULL;
    list->Count = 0;
    return list;
}

void LinkedList_AddNode(LinkedList *list, T3_Node *node, uint index) {
    T3_Assert(index > list->Count, "OutOfRange index!");
    
    //Insert at the beginning of the linked list
    if (index == 0){
        node->Ptr1 = list->Head;
        list->Head = node;

        if (list->Count == 0){
            list->Tail = node;
        }
    }
    //Insert at the end of the linked list
    else if (index == list->Count){
        list->Tail->Ptr1 = node;
        list->Tail = node;
    }
    //Insert at specific index of the linked list
    else{
        T3_Node* current = list->Head;
        for (uint i = 0; i < index; i++){
            current = current->Ptr1;
        }
        node->Ptr1 = current->Ptr1;
        current->Ptr1 = node;
    }
    list->Count++;
}

void LinkedListDouble_AddNode(LinkedListDouble *list, T3_NodeDouble *node, uint index) {
    T3_Assert(index > list->Count, "OutofRange index!");

    //Insert at the beginning of the double linked list
    if (index == 0) {
        node->Ptr1 = list->Head;
        if (list->Head != NULL) {
            list->Head->Ptr2 = node;
        }
        else {
            list->Tail = node;
        }
        list->Head = node;
    }
    //Insert at the end of the double linked list
    else if (index == list->Count) {
        list->Tail->Ptr1 = node;
        node->Ptr2 = list->Tail;
        list->Tail = node;
    }
    //Inset at a specific index of the double linked list
    else {
        T3_NodeDouble* current = list->Head;
        for (uint i = 0; i < index; i++) {
            current = current->Ptr1;
        }
        node->Ptr1 = current->Ptr1;
        node->Ptr2 = current;
        current->Ptr1 = node;
        node->Ptr1->Ptr2 = node;
    }
    list->Count++;
}

T3_Node *LinkedList_GetNode(LinkedList *list, uint index) {
    T3_Assert(index >= list->Count, "OutOfRange search!");

    if (index == 0){
        return list->Head;
    }
    else if (index == list->Count-1){
        return list->Tail;
    }else{
        T3_Node *current = list->Head;
        for (int i = 0; i < index; ++i) {
            current = current->Next;
        }
        return current;    
    }
}

//LinkedListDouble_GetNode has the same logic of LinkedList_GetNode
T3_NodeDouble* LinkedListDouble_GetNode(LinkedListDouble* list, uint index) {
    LinkedList_GetNode(list, index);
}

void LinkedList_Remove(LinkedList* list, T3_Node* node) {
    T3_Assert(list->Count <= 0, "Cannot remove from an empty list");

    //Remove from the beginning of the linked list
    if (node == list->Head) {
        list->Head = node->Ptr1;
        //Take into consideration only one element in the linked list
        if (list->Count == 1) {
            list->Tail = NULL;
        }
    }
    //Remove from a specific position of the linked list
    else {
        T3_Node* current = list->Head;
        while (current->Ptr1 != node) {
            current = current->Ptr1;
        }
        current->Ptr1 = node->Ptr1;

        if (node == list->Tail) {
            list->Tail = current;
        }
    }
    free(node);
    list->Count--;
}

void LinkedListDouble_Remove(LinkedListDouble* list, T3_NodeDouble* node) {
    T3_Assert(list->Count <= 0, "Cannot remove from an empty list");

    //Remove from the beginning of the double linked list
    if (node == list->Head) {
        list->Head = node->Ptr1;
        if (list->Head != NULL) {
            list->Head->Ptr2 = NULL;
        }
        else {
            list->Tail = NULL;
        }
    }
    //Remove from a specific position of the double linked list
    else {
        T3_NodeDouble* current = list->Head;
        while (current->Ptr1 != node) {
            current = current->Ptr1;
        }
        current->Ptr1 = node->Ptr1;
        if (node->Ptr1 != NULL) {
            node->Ptr1->Ptr2 = current;
        }
        else {
            list->Tail = current;
        }
    }
    free(node);
    list->Count--;
}

void LinkedList_RemoveAt(LinkedList* list, uint index) {
    T3_Assert(index > list->Count, "OutofRange index!");
    T3_Node* node = LinkedList_GetNode(list, index);
    LinkedList_Remove(list, node);
}

void LinkedListDouble_RemoveAt(LinkedListDouble* list, uint index) {
    T3_Assert(index > list->Count, "OutofRange index!");
    T3_NodeDouble* node = LinkedListDouble_GetNode(list, index);
    LinkedListDouble_Remove(list, node);
}

void LinkedList_DestroyNode(LinkedList* list, T3_Node* node) {
    LinkedList_Remove(list, node);
}

void LinkedListDouble_DestroyNode(LinkedListDouble* list, T3_NodeDouble* node) {
    LinkedListDouble_Remove(list, node);
}

void LinkedList_DestroyNodeAt(LinkedList* list, uint index) {
    T3_Assert(index > list->Count, "OutofRange index!");
    T3_Node* node = LinkedList_GetNode(list, index);
    LinkedListDouble_DestroyNode(list, node);
}

void LinkedListDouble_DestroyNodeAt(LinkedListDouble* list, uint index) {
    T3_Assert(index > list->Count, "OutofRange index!");
    T3_NodeDouble* node = LinkedListDouble_GetNode(list, index);
    LinkedListDouble_DestroyNode(list, node);
}

void LinkedList_Destroy(LinkedList* list) {
    while (list->Head != NULL) {
        LinkedList_Remove(list, list->Head);
    }
    free(list);
}

void LinkedListDouble_Destroy(LinkedListDouble* list) {
    while (list->Head != NULL) {
        LinkedListDouble_Remove(list, list->Head);
    }
    free(list);
}