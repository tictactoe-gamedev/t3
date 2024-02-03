#include "core/helpers.h"
#include "core/abstract-data-types.h"

T3_LinkedList *T3_LinkedList_Init() {
    T3_HELPER_MALLOC_SAFE(T3_LinkedList, list);
    list->Head = NULL;
    list->Tail = NULL;
    list->Count = 0;
    return list;
}

void T3_LinkedList_AddNode(T3_LinkedList *list, T3_Node *node, size_t index) {
    if (index == 0) {
        T3_LinkedList_AddToHead(list, node);
    } else if (index == list->Count) {
        T3_LinkedList_AddToTail(list, node);
    } else {
        T3_LinkedList_AddToIndex(list, node, index);
    }
}

void T3_LinkedList_AddToHead(T3_LinkedList *list, T3_Node *node) {
    uint listCount = list->Count;

    if (listCount == 0) {
        list->Head = node;
    } else if (listCount == 1) {
        list->Tail = list->Head;
        list->Head = node;
        list->Head->Next = list->Tail;
    } else {
        node->Next = list->Head;
        list->Head = node;
    }

    list->Count++;
}

void T3_LinkedList_AddToTail(T3_LinkedList *list, T3_Node *node) {

    if (list->Count == 1) {
        list->Tail = node;
        list->Head->Next = list->Tail;
    } else {
        list->Tail->Next = node;
        list->Tail = node;
    }

    list->Count++;
}

void T3_LinkedList_AddToIndex(T3_LinkedList *list, T3_Node *node, size_t index) {
    T3_HELPER_ASSERT(index < list->Count, "OutOfRange index!");
    T3_HELPER_ASSERT(!(index == 0 || index == list->Count), "Adding to head or tail. Use AddNode instead!");

    T3_Node *found = T3_LinkedList_GetNode(list, index - 1);
    node->Next = found->Next;
    found->Next = node;

    list->Count++;
}

T3_Node *T3_LinkedList_GetNode(T3_LinkedList *list, size_t index) {
    T3_HELPER_ASSERT(index < list->Count, "OutOfRange index!");

    if (index == 0) {
        return list->Head;
    }

    if (index == list->Count - 1) {
        return list->Tail;
    }

    T3_Node *current = list->Head;
    int i = 0;
    for (i = 0; i < index; ++i) {
        current = current->Next;
    }
    return current;
}

void T3_LinkedList_Remove(T3_LinkedList *list, T3_Node *node) {
    T3_HELPER_ASSERT(list->Count != 0, "Nothing to remove");

    T3_Node *current = list->Head;

    if (current == node) {
        if (list->Count == 1) {
            list->Head = NULL;
        } else if (list->Count == 2) {
            list->Head = list->Tail;
            list->Head->Next = NULL;
            list->Tail = NULL;
        } else {
            list->Head = list->Head->Next;
        }
        list->Count--;
        return;
    }

    int i;
    for (i = 0; i < list->Count - 2; ++i) {
        if (current->Next == node) {
            current->Next = node->Next;
            list->Count--;
            return;
        }
        current = current->Next;
    }

    if (current->Next == node) {
        if (list->Count == 2) {
            list->Head->Next = NULL;
        } else {
            list->Tail = current;
            list->Tail->Next = NULL;
        }
        list->Count--;
        return;
    }

}

size_t T3_LinkedList_FindIndexOf(T3_LinkedList *list, T3_Node *node) {
    if (node == list->Tail) {
        return list->Count - 1;
    }
    if (node == list->Head) {
        return 0;
    }

    T3_Node *current = list->Head->Next;
    size_t i;
    for (i = 0; i < list->Count - 2; ++i) {
        if (current == node) {
            return i;
        }
        current = current->Next;
    }
    return -1;
}

//TODO: Below functions can still optimized!
T3_Node *T3_LinkedList_RemoveAt(T3_LinkedList *list, size_t index) {
    T3_Node *removed = T3_LinkedList_GetNode(list, index);
    T3_LinkedList_Remove(list, removed);
    return removed;
}

void T3_LinkedList_DestroyNodeAt(T3_LinkedList *list, size_t index) {
    T3_Node *node = T3_LinkedList_GetNode(list, index);
    T3_LinkedList_Remove(list, node);
    T3_Node_Destroy(node);
}

void T3_LinkedList_DestroyNode(T3_LinkedList *list, T3_Node *node) {
    T3_LinkedList_Remove((list), (node));
    T3_Node_Destroy(node);
}

void T3_LinkedList_Destroy(T3_LinkedList *list) {
    if (list->Count > 0) {
        T3_Node *current = list->Head;
        int i;
        for (i = 0; i < list->Count; ++i) {
            T3_Node *remove = current;
            T3_LinkedList_Remove(list, remove);
            T3_Node_Destroy(remove);
            current = current->Next;
        }
    }

    free(list);
}

void T3_LinkedList_Log_Int(T3_LinkedList *list) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    int i = 0;
    T3_Node *node = list->Head;
    while (node != NULL) {
        T3_HELPER_LOG(Info, "[%d]: [%d]", i, *(int*)node->Data);
        node = node->Next;
        i++;
    }
#endif
}

void T3_LinkedList_Test() {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    T3_LinkedList *list = T3_LinkedList_Init();

    T3_LinkedList_AddToHead(list, T3_Node_Init_Int(2));
    T3_LinkedList_AddToHead(list, T3_Node_Init_Int(5));

    T3_LinkedList_Log_Int(list);
    
    T3_LinkedList_RemoveAt(list, 0);
    T3_Node *node = T3_LinkedList_GetNode(list, 0);
    size_t index = T3_LinkedList_FindIndexOf(list, node);
    T3_HELPER_LOG(Info, "Found Index: %d", index);

    T3_LinkedList_AddToTail(list, T3_Node_Init_Int(23));  
    T3_LinkedList_Log_Int(list);

    T3_LinkedList_AddNode(list, T3_Node_Init_Int(-12), 1); 

    T3_LinkedList_Remove(list, node);
    T3_Node_Destroy(node);

    T3_LinkedList_Destroy(list);
#endif
}

T3_LinkedListDouble *T3_LinkedListDouble_Init() {
    T3_HELPER_MALLOC_SAFE(T3_LinkedListDouble, list);
    list->Head = NULL;
    list->Tail = NULL;
    list->Count = 0;
    return list;
}

/**
 * Add node without considering if its head, tail or between. Secure but relatively slow
 */
void T3_LinkedListDouble_AddNode(T3_LinkedListDouble *list, T3_NodeDouble *node, size_t index) {
    if (index == 0) {
        T3_LinkedListDouble_AddToHead(list, node);
    } else if (index == list->Count) {
        T3_LinkedListDouble_AddToTail(list, node);
    } else {
        T3_LinkedListDouble_AddToIndex(list, node, index);
    }
}


void T3_LinkedListDouble_AddToHead(T3_LinkedListDouble *list, T3_NodeDouble *node) {
    uint listCount = list->Count;

    if (listCount == 0) {
        list->Head = node;
    } else if (listCount == 1) {
        list->Tail = list->Head;
        list->Head = node;
        list->Head->Next = list->Tail;
        list->Tail->Prev = list->Head;
    } else {
        node->Next = list->Head;
        list->Head->Prev = node;
        list->Head = node;
    }

    list->Count++;
}


void T3_LinkedListDouble_AddToTail(T3_LinkedListDouble *list, T3_NodeDouble *node) {

    if (list->Count == 1) {
        list->Tail = node;
        list->Head->Next = list->Tail;
        list->Tail->Prev = list->Head;
    } else {
        list->Tail->Next = node;
        node->Prev = list->Tail;
        list->Tail = node;
    }

    list->Count++;
}


/**
 * Use it ONLY if you know the position is not head or tail
 * @param list 
 * @param node 
 * @param index 
 */
void T3_LinkedListDouble_AddToIndex(T3_LinkedListDouble *list, T3_NodeDouble *node, size_t index) {
    T3_HELPER_ASSERT(index < list->Count, "OutOfRange index!");
    T3_HELPER_ASSERT(!(index == 0 || index == list->Count), "Adding to head or tail. Use AddNode instead!");

    T3_NodeDouble *found = T3_LinkedListDouble_GetNode(list, index - 1);
    node->Next = found->Next;
    found->Next->Prev = node;
    found->Next = node;
    node->Prev = found;

    list->Count++;
}


T3_NodeDouble *T3_LinkedListDouble_GetNode(T3_LinkedListDouble *list, size_t index) {
    T3_HELPER_ASSERT(index < list->Count, "OutOfRange index!");

    if (index == 0) {
        return list->Head;
    }

    if (index == list->Count - 1) {
        return list->Tail;
    }

    if (index <= list->Count / 2) {
        T3_NodeDouble *current = list->Head;
        size_t i;
        for (i = 0; i < index; ++i) {
            current = current->Next;
        }
        return current;
    }

    T3_NodeDouble *current = list->Tail;
    size_t i;
    for (i = list->Count; i > index; --i) {
        current = current->Prev;
    }
    return current;

}


void T3_LinkedListDouble_Remove(T3_LinkedListDouble *list, T3_NodeDouble *node) {
    T3_HELPER_ASSERT(list->Count != 0, "Nothing to remove");

    T3_NodeDouble *current = list->Head;

    if (current == node) {
        if (list->Count == 1) {
            list->Head = NULL;
        } else if (list->Count == 2) {
            list->Head = list->Tail;
            list->Head->Next = NULL;
            list->Head->Prev = NULL;
            list->Tail = NULL;
        } else {
            list->Head = list->Head->Next;
            list->Head->Prev = NULL;
        }
        list->Count--;
        return;
    }

    int i;
    for (i = 0; i < list->Count - 2; ++i) {
        if (current->Next == node) {
            current->Next = node->Next;
            node->Next->Prev = current;
            list->Count--;
            return;
        }
        current = current->Next;
    }

    if (current->Next == node) {
        if (list->Count == 2) {
            list->Head->Next = NULL;
        } else {
            list->Tail = current;
            list->Tail->Next = NULL;
        }
        list->Count--;
        return;
    }
}


size_t T3_LinkedListDouble_FindIndexOf(T3_LinkedListDouble *list, T3_NodeDouble *node) {
    if (node == list->Tail) {
        return list->Count - 1;
    }

    if (node == list->Head) {
        return 0;
    }

    T3_NodeDouble *current = list->Head->Next;
    size_t i;
    for (i = 0; i < list->Count - 2; ++i) {
        if (current == node) {
            return i;
        }
        current = current->Next;
    }
    return -1;
}


T3_NodeDouble *T3_LinkedListDouble_RemoveAt(T3_LinkedListDouble *list, size_t index) {
    T3_NodeDouble *removed = T3_LinkedListDouble_GetNode(list, index);
    T3_LinkedListDouble_Remove(list, removed);
    return removed;
}


void T3_LinkedListDouble_DestroyNode(T3_LinkedListDouble *list, T3_NodeDouble *node) {
    T3_LinkedListDouble_Remove((list), (node));
    T3_NodeDouble_Destroy(node);
}


void T3_LinkedListDouble_DestroyNodeAt(T3_LinkedListDouble *list, size_t index) {
    T3_NodeDouble *node = T3_LinkedListDouble_GetNode(list, index);
    T3_LinkedListDouble_Remove(list, node);
    T3_NodeDouble_Destroy(node);
}

void T3_LinkedListDouble_Destroy(T3_LinkedListDouble *list) {
    if (list->Count > 0) {
        T3_NodeDouble *current = list->Head;
        int i;
        for (i = 0; i < list->Count; ++i) {
            T3_NodeDouble *remove = current;
            T3_LinkedListDouble_Remove(list, remove);
            T3_NodeDouble_Destroy(remove);
            current = current->Next;
        }
    }

    free(list);
}

void T3_LinkedListDouble_Log_Int(T3_LinkedListDouble *list) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    int i = 0;
    T3_NodeDouble *node = list->Head;
    while (node != NULL) {
        T3_HELPER_LOG(Info, "[%d]: [%d]", i, *(int*)node->Data);
        node = node->Next;
        i++;
    }
#endif
}

void T3_LinkedListDouble_Test() {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    T3_LinkedListDouble *list = T3_LinkedListDouble_Init();
    
    T3_LinkedListDouble_AddToHead(list, T3_NodeDouble_Init_Int(2));
    T3_LinkedListDouble_AddToHead(list, T3_NodeDouble_Init_Int(5));
    T3_LinkedListDouble_Log_Int(list);
    
    T3_LinkedListDouble_RemoveAt(list, 0);
    T3_NodeDouble *node = T3_LinkedListDouble_GetNode(list, 0);
    size_t index = T3_LinkedListDouble_FindIndexOf(list, node);
    T3_HELPER_LOG(Info, "Found Index: %d", index);

    T3_LinkedListDouble_AddToTail(list, T3_NodeDouble_Init_Int(23));
    T3_LinkedListDouble_Log_Int(list);

    T3_LinkedListDouble_AddNode(list, T3_NodeDouble_Init_Int(-12), 1);

    T3_LinkedListDouble_Remove(list, node);
    T3_NodeDouble_Destroy(node);

    T3_LinkedListDouble_Destroy(list);
#endif
}