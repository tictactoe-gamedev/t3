#include <stdio.h>
#include "helpers.h"
#include "adt.h"

size_t GetRealIndex(T3_List *list, size_t index);

T3_List *T3_List_Init(size_t initialCapacity) {
    T3_List *list = T3_Helper_Malloc_Safe(sizeof *list, T3_FILE_LINE);
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->Array = (void **) malloc(sizeof(void *) * initialCapacity);
    list->_removedIndices = (size_t *) malloc(sizeof(size_t) * initialCapacity / 2);
    list->_removedIndicesSize = 0;
    list->_removedIndicesCapacity = initialCapacity / 2;
    return list;
}

T3_List *T3_List_Init_With_Elements(size_t initialCapacity, size_t elementsCount, ...) {
    int i;
    va_list args;
    
    T3_List *list = T3_Helper_Malloc_Safe(sizeof *list, T3_FILE_LINE);
    list->Capacity = initialCapacity;
    list->Size = 0;
    list->Array = (void **) malloc(sizeof(void *) * initialCapacity);
    list->_removedIndices = (size_t *) malloc(sizeof(size_t) * initialCapacity / 2);
    list->_removedIndicesSize = 0;
    list->_removedIndicesCapacity = initialCapacity / 2;

    va_start(args, elementsCount);
    for (i = 0; i < elementsCount; ++i) {
        list->Array[list->Size + list->_removedIndicesSize] = va_arg(args, void*);
        list->Size++;
    }
    va_end(args);
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

void T3_List_Resize(T3_List *list, size_t newCapacity) {
    list->Capacity = newCapacity;
    list->Array = (void **) realloc(list->Array, sizeof(void *) * newCapacity);
    T3_Helper_Error_If(list->Array == NULL, __FILE__, __LINE__, "Can't re-alloc");
}

void T3_List_ResizeCache(T3_List *list, size_t newCapacity) {
    list->_removedIndicesCapacity = newCapacity;
    list->_removedIndices = (size_t *) realloc(list->_removedIndices, sizeof(size_t) * newCapacity);
    T3_Helper_Error_If(list->_removedIndices == NULL, __FILE__, __LINE__, "Can't re-alloc");
}

void T3_List_Remove(T3_List *list, void *element) {
    size_t i;
    for (i = 0; i < list->Size + list->_removedIndicesSize; ++i) {
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
    size_t i;
    for (i = 0; i < list->Size + list->_removedIndicesSize; ++i) {
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

void *T3_List_RemoveAt(T3_List *list, size_t index) {
    void *removed = list->Array[GetRealIndex(list, index)];
    T3_List_Remove(list, removed);
    return removed;
}

void *T3_List_RemoveAtSafe(T3_List *list, size_t index) {
    void *removed = list->Array[GetRealIndex(list, index)];
    T3_List_RemoveSafe(list, removed);
    return removed;
}

/*TODO: Make something like SetDirty so you won't need to calculate offset again and again*/
size_t GetRealIndex(T3_List *list, size_t index) {
    size_t offset;
    size_t i;
    if (list->_removedIndicesSize == 0) {
        return index;
    }

    offset = 0;
    for (i = 0; i < list->_removedIndicesSize; ++i) {   /*TODO: They must be a sorted list to make it efficient really!*/
        if (list->_removedIndices[i] <= index + offset) {
            offset++;
        }
    }

    return index + offset;
}

void T3_List_CleanCache(T3_List *list) {
    size_t shiftAmount = 0;
    size_t i;
    for (i = 0; i < list->_removedIndicesSize + list->Size; ++i) {
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
            (size_t *) realloc(list->_removedIndices, sizeof(size_t) * list->_removedIndicesCapacity);
    list->_removedIndicesSize = 0;
}

/*TODO: We need a better iterator!*/
void *T3_List_Get(T3_List *list, size_t index) {
    return list->Array[GetRealIndex(list, index)];
}

void T3_List_Destroy(T3_List *list) {
    free(list->Array);
    free(list->_removedIndices);
    free(list);
}

void T3_List_Set(T3_List *list, size_t index, void *element) {
    list->Array[GetRealIndex(list, index)] = element;
}

int T3_List_FindIndexOf(T3_List *list, void *element) {
    int i;
    for (i = 0; i < list->Size + list->_removedIndicesSize; ++i) {
        if (list->Array[i] == NULL) {
            continue;
        }

        if (list->Array[i] == element) {
            return i;
        }
    }
    return -1;
}


void T3_List_Test(void) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    size_t t;
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

    
    for (t = 0; t < 9; t++) {
        printf("%d\n", *(int *) T3_List_Get(list, t));
    }

    T3_List_RemoveSafe(list, &a);
    T3_List_RemoveSafe(list, &c);
    T3_List_RemoveSafe(list, &e);
    T3_List_RemoveSafe(list, &h);

    for (t = 0; t < 5; t++) {
        printf("%d\n", *(int *) T3_List_Get(list, t));
    }

    T3_List_Add(list, &a);
    T3_List_Add(list, &h);

    for (t = 0; t < 7; t++) {
        printf("%d\n", *(int *) T3_List_Get(list, t));
    }

#endif
}
