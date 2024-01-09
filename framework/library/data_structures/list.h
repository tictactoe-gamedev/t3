#ifndef T3_LIST_H
#define T3_LIST_H

#include <cstdlib>

typedef struct T3_List {
    void **Array;
    uint Capacity;
    uint Size;
    uint *_removedIndices;
    uint _removedIndicesSize;
    uint _removedIndicesCount;
} T3_List;

T3_List *T3_List_Init(uint initialCapacity);

void T3_List_Add(T3_List *list, void *element);

void T3_List_Remove(T3_List *list, void *element);

#endif //T3_LIST_H