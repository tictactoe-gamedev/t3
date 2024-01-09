#include <cstdio>
#include "list.h"
#include "helper/memory.h"

uint GetRealIndex(T3_List *list, uint index);

T3_List *T3_List_Init(uint initialCapacity) {
    T3_MallocSafe(T3_List, list)
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->Array = (void **) malloc(sizeof(void *) * initialCapacity);
    list->_removedIndices = (uint *) malloc(sizeof(uint) * initialCapacity / 2);
    list->_removedIndicesSize = 0;
    list->_removedIndicesCapacity = initialCapacity / 2;
    return list;
}

void T3_List_AddSafe(T3_List *list, void *element) {
    if (list->Size + 1 > list->Capacity) {
        T3_List_Resize(list, list->Capacity * 2);
    }
    T3_List_Add(list, element);
}

void T3_List_Add(T3_List *list, void *element) {
    list->Array[list->Size + list->_removedIndicesSize] = element;
    list->Size++;
}

void T3_List_Resize(T3_List *list, uint newCapacity) {
    list->Capacity = newCapacity;
    list->Array = (void **) realloc(list->Array, sizeof(void *) * newCapacity);
    T3_ErrorIf(list->Array==NULL, "Can't re-alloc");
}

void T3_List_ResizeCache(T3_List *list, uint newCapacity) {
    list->_removedIndicesCapacity = newCapacity;
    list->_removedIndices = (uint *) realloc(list->_removedIndices, sizeof(uint) * newCapacity);
    T3_ErrorIf(list->_removedIndices==NULL, "Can't re-alloc");
}

void T3_List_Remove(T3_List *list, void *element) {
    for (uint i = 0; i < list->Size + list->_removedIndicesSize; ++i) {
        if (list->Array[i] == NULL) {
            continue;
        }

        if (list->Array[i] == element) {
            list->Array[i] = NULL;
            list->_removedIndices[list->_removedIndicesSize] = i;
            list->_removedIndicesSize++;
            list->Size--;
            return;
        }
    }
}

void T3_List_RemoveSafe(T3_List *list, void *element) {
    for (uint i = 0; i < list->Size + list->_removedIndicesSize; ++i) {
        if (list->Array[i] == NULL) {
            continue;
        }

        if (list->Array[i] == element) {
            list->Array[i] = NULL;
            list->_removedIndices[list->_removedIndicesSize] = i;
            list->_removedIndicesSize++;
            list->Size--;

            if (list->_removedIndicesSize == list->_removedIndicesCapacity - 1) {
                T3_List_CleanCache(list);
            }
            return;
        }
    }
}

void *T3_List_RemoveAt(T3_List *list, uint index) {
    void* removed = list->Array[GetRealIndex(list,index)];
    T3_List_Remove(list, removed);
    return removed;
}

void *T3_List_RemoveAtSafe(T3_List *list, uint index) {
    void* removed = list->Array[GetRealIndex(list,index)];
    T3_List_RemoveSafe(list, removed);
    return removed;
}

uint GetRealIndex(T3_List *list, uint index) {
    if (list->_removedIndicesSize == 0) {
        return index;
    }

    uint offset = 0;
    for (uint i = 0; i < list->_removedIndicesSize; ++i) {   //TODO: They must be a sorted list to make it efficient really!
        if (list->_removedIndices[i] <= index + offset) {
            offset++;
        }
    }

    return index + offset;
}

void T3_List_CleanCache(T3_List *list) {
    uint shiftAmount = 0;
    
    for (uint i = 0; i < list->_removedIndicesSize + list->Size; ++i) {
        if (list->Array[i] == NULL) {
            shiftAmount++;
            continue;
        }
        if (shiftAmount == 0) {
            continue;
        }
        list->Array[i - shiftAmount] = list->Array[i];
        list->Array[i] = NULL;
    }


    list->_removedIndices = 
            (uint *) realloc(list->_removedIndices, sizeof(uint) * list->_removedIndicesCapacity);
    list->_removedIndicesSize = 0;
}

void *T3_List_Get(T3_List *list, uint index) {
    return list->Array[GetRealIndex(list, index)];
}

void T3_List_Destroy(T3_List *list) {
    free(list->Array);
    free(list->_removedIndices);
    free(list);
}

void T3_List_Set(T3_List *list, uint index, void *element) {
    list->Array[GetRealIndex(list,index)]=element;
}

int T3_List_FindIndexOf(T3_List *list, void* element) {
    for (int i = 0; i < list->Size + list->_removedIndicesSize; ++i) {
        if (list->Array[i] == NULL) {
            continue;
        }

        if (list->Array[i] == element) {
            return i;
        }
    }  
    return -1;
}


void T3_List_Test() {
#ifdef GAME_RELEASE
#if GAME_RELEASE == DEVELOPMENT
    T3_List *list = T3_List_Init(10);
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    int g = 7;
    int h = 8;
    int i = 9;
    T3_List_Add(list, &a);
    T3_List_Add(list, &b);
    T3_List_Add(list, &c);
    T3_List_Add(list, &d);
    T3_List_Add(list, &e);
    T3_List_Add(list, &f);
    T3_List_Add(list, &g);
    T3_List_Add(list, &h);
    T3_List_Add(list, &i);

    for (uint t = 0; t < 9; t++) {
        printf("%d\n", *(int *) T3_List_Get(list, t));
    }

    T3_List_RemoveSafe(list, &a);
    T3_List_RemoveSafe(list, &c);
    T3_List_RemoveSafe(list, &e);
    T3_List_RemoveSafe(list, &h);

    for (uint k = 0; k < 5; k++) {
        printf("%d\n", *(int *) T3_List_Get(list, k));
    }

    T3_List_Add(list, &a);
    T3_List_Add(list, &h);

    for (uint v = 0; v < 7; v++) {
        printf("%d\n", *(int *) T3_List_Get(list, v));
    }

#endif
#endif
}


