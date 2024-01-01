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
    
}

void LinkedListDouble_AddNode(LinkedListDouble *list, T3_NodeDouble *node, uint index) {


}

T3_Node *LinkedList_GetNode(LinkedList *list, uint index) {
    T3_Assert(index >= list->Count, "OutOfRange search");

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
