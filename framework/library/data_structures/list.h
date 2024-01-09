#ifndef T3_LIST_H
#define T3_LIST_H

#include <cstdlib>

typedef struct T3_List {
    void **Array;
    uint Capacity;
    uint Size;
    uint *_removedIndices;
    uint _removedIndicesSize;
    uint _removedIndicesCapacity;
} T3_List;

/**
 * Initialize a list with initialCapacity and initialCapacity/2 cache for removed items
 * @param initialCapacity 
 * @return 
 */
T3_List *T3_List_Init(uint initialCapacity);

/**
 * Checks if there's a capacity overflow. If so, increase the capacity x 2
 * @param list 
 * @param element 
 */
void T3_List_AddSafe(T3_List *list, void *element);

void T3_List_Add(T3_List *list, void *element);

void T3_List_Remove(T3_List* list, void *element);

/**
 * Remove item from list. 
 * Also checks if the removed item cache is overflowed. Flushes the cache if necessary
 * @param list 
 * @param element 
 */
void T3_List_RemoveSafe(T3_List *list, void *element);


void* T3_List_RemoveAt(T3_List *list, uint index);
void* T3_List_RemoveAtSafe(T3_List *list, uint index);

void T3_List_Resize(T3_List *list, uint newCapacity);

/**
 * Changes the capacity of cached elements which are removed from the list
 * @param list 
 * @param newCapacity 
 */
void T3_List_ResizeCache(T3_List *list, uint newCapacity);

void *T3_List_Get(T3_List *list, uint index);

int T3_List_FindIndexOf(T3_List* list, void* element);

void T3_List_Set(T3_List *list, uint index, void* element);

/**
 * Cleans the removed elements cache. 
 * It's automatically cleaned when the removed item count reaches the capacity.
 * @param list 
 */
void T3_List_CleanCache(T3_List *list);

void T3_List_Destroy(T3_List* list);

void T3_List_Test();


#endif //T3_LIST_H