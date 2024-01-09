#include "list.h"
#include "helper/memory.h"

inline void T3_List_ResizeControl(T3_List *list);

T3_List *T3_List_Init(uint initialCapacity) {
    T3_MallocSafe(T3_List, list)
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->Array = (void **) malloc(sizeof(void *) * initialCapacity);
    list->_removedIndices = (uint *) malloc(sizeof(uint) * initialCapacity / 2);
    list->_removedIndicesSize = 0;
    return list;
}

void T3_List_Add(T3_List *list, void *element) {
    T3_List_ResizeControl(list);
}


void T3_List_ResizeControl(T3_List *list) {
    if (list->Size * 2 > list->Capacity) {
        list->Capacity *= 2;
        list->Array = (void **) realloc(list->Array, sizeof(void *) * list->Capacity);
    }
}