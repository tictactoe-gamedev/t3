#include "linked_list.h"
#include "helper/memory.h"
#include "helper/logging.h"

#define Next Ptr1
#define Prev Ptr2

T3_LinkedList *T3_LinkedList_Init() {
    T3_MallocSecure(T3_LinkedList, list);
    list->Head = NULL;
    list->Tail = NULL;
    list->Count = 0;
    return list;
}

T3_LinkedListDouble *T3_LinkedListDouble_Init() {
    T3_MallocSecure(T3_LinkedListDouble, list);
    list->Head = NULL;
    list->Tail = NULL;
    list->Count = 0;
    return list;
}

void T3_LinkedList_AddNode(T3_LinkedList *list, T3_Node *node, uint index) {
    T3_Assert(index > list->Count, "OutOfRange index!");

    if (index == 0) {
        if (list->Count != 0) {
            node->Next = list->Head;
        }
        list->Head = node;
    } else if (index == list->Count) {
        if (list->Count != 1) {
            list->Tail->Next = node;
        }
        list->Tail = node;
    } else {
        T3_Node *found = T3_LinkedList_GetNode(list, index - 1);
        node->Next = found->Next;
        found->Next = node;
    }

    list->Count++;
}

void T3_LinkedListDouble_AddNode(T3_LinkedListDouble *list, T3_NodeDouble *node, uint index) {
    T3_Assert(index > list->Count, "OutOfRange index!");

    if (index == 0) {
        if (list->Count != 0) {
            node->Next = list->Head;
            list->Head->Prev = node;
        }
        list->Head = node;
    } else if (index == list->Count) {
        if (list->Count != 1) {
            list->Tail->Next = node;
            node->Prev = list->Tail;
        }
        list->Tail = node;
    } else {
        T3_NodeDouble *found = T3_LinkedListDouble_GetNode(list, index - 1);
        node->Next = found->Next;
        found->Next->Prev = node;
        found->Next = node;
        node->Prev = found;
    }

    list->Count++;

}

T3_Node *T3_LinkedList_GetNode(T3_LinkedList *list, uint index) {
    if (index == 0) {
        return list->Head;
    }

    if (index == list->Count - 1) {
        return list->Tail;
    }

    T3_Node *current = list->Head;
    for (int i = 0; i < index; ++i) {
        current = current->Next;
    }
    return current;

}

T3_NodeDouble *T3_LinkedListDouble_GetNode(T3_LinkedListDouble *list, uint index) {
    if (index == 0) {
        return list->Head;
    }
    
    if (index == list->Count - 1) {
        return list->Tail;
    }
    
    if (list->Count / 2 <= index) {
        T3_NodeDouble *current = list->Head;
        for (uint i = 0; i < index; ++i) {
            current = current->Next;
        }
        return current;
    }
    
    T3_NodeDouble *current = list->Tail;
    for (uint i = list->Count - 1; i > index; --i) {
        current = current->Prev;
    }
    return current;
    
}

void T3_LinkedList_Remove(T3_LinkedList *list, T3_Node *node) {
    T3_Node *previous = NULL;
    T3_Node *current = list->Head;

    for (int i = 0; i < list->Count; ++i) {
        if (current == node) {
            if (i == 0) {
                list->Head = list->Head->Next;
                if (list->Count == 2) {
                    list->Tail = NULL;
                }
            } else if (i == list->Count - 1) {
                if (list->Count > 2) {
                    list->Tail = previous;
                    list->Tail->Next = NULL;
                } else {
                    list->Tail = NULL;
                }
            } else {
                previous->Next = current->Next;
            }
            list->Count--;
            return;
        }
        previous = current;
        current = current->Next;
    }
}

void T3_LinkedListDouble_Remove(T3_LinkedListDouble *list, T3_NodeDouble *node) {

    if (list->Head == node) {
        list->Head = list->Head->Next;
        list->Head->Prev = NULL;

        if (list->Count == 2) {
            list->Tail = NULL;
        }
    } else if (list->Tail == node) {
        if (list->Count > 2) {
            list->Tail = list->Tail->Prev;
            list->Tail->Next = NULL;
        } else {
            list->Tail = NULL;
        }
    } else {
        node->Prev->Next = node->Next;
        node->Next->Prev = node->Prev;
    }

    list->Count--;
    return;
}

uint T3_LinkedList_FindIndexOf(T3_LinkedList *list, T3_Node *node) {
    if (node == list->Tail) {
        return list->Count - 1;
    }

    T3_Node *current = list->Head;
    for (uint i = 0; i < list->Count; ++i) {
        if (current == node) {
            return i;
        }
    }
    return -1;
}

uint T3_LinkedListDouble_FindIndexOf(T3_LinkedListDouble *list, T3_NodeDouble *node) {
    if (node == list->Tail) {
        return list->Count - 1;
    }

    T3_NodeDouble *current = list->Head;
    for (uint i = 0; i < list->Count; ++i) {
        if (current == node) {
            return i;
        }
    }
    return -1;
}

void T3_LinkedList_RemoveAt(T3_LinkedList *list, uint index) {
    T3_Node *removed = T3_LinkedList_GetNode(list, index);
    T3_LinkedList_Remove(list, removed);
}

void T3_LinkedListDouble_RemoveAt(T3_LinkedListDouble *list, uint index) {
    T3_NodeDouble *removed = T3_LinkedListDouble_GetNode(list, index);
    T3_LinkedListDouble_Remove(list, removed);
}

void T3_LinkedList_DestroyNode(T3_LinkedList *list, T3_Node *node) {
    T3_LinkedList_Remove((list), (node));
    T3_Node_Destroy(node);
}

void T3_LinkedListDouble_DestroyNode(T3_LinkedListDouble *list, T3_NodeDouble *node) {
    T3_LinkedListDouble_Remove((list), (node));
    T3_NodeDouble_Destroy(node);
}

void T3_LinkedList_DestroyNodeAt(T3_LinkedList *list, uint index) {
    T3_Node *node = T3_LinkedList_GetNode(list, index);
    T3_LinkedList_Remove(list, node);
    T3_Node_Destroy(node);
}

void T3_LinkedListDouble_DestroyNodeAt(T3_LinkedListDouble *list, uint index) {
    T3_NodeDouble *node = T3_LinkedListDouble_GetNode(list, index);
    T3_LinkedListDouble_Remove(list, node);
    T3_NodeDouble_Destroy(node);
}
