#include "list.h"
#include "helper/memory.h"

T3_List *T3_List_Init(uint initialCapacity) {
    T3_MallocSafe(T3_List, list)
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->Array = (void **) malloc(sizeof(void *) * initialCapacity);
    list->_removedIndices = (uint *) malloc(sizeof(uint) * initialCapacity / 2);
    list->_removedIndicesSize = 0;
    return list;
}
