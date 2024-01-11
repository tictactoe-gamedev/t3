#ifndef T3_ENTITY_H
#define T3_ENTITY_H

#include "library/data_structures/list.h"
#include "helper/memory.h" 

typedef struct T3_Entity {
    const char *EntityName;
    const char *InstanceName;
    T3_List *Components;
    T3_Entity *Parent;
    T3_List *Children;
} T3_Entity;

#define T3_EntityHeader(__EntityName, __Body, ...)\
T3_Entity* T3_Entity_##__EntityName(const char * instanceName, ## __VA_ARGS__){ \
    T3_MallocSafe(T3_Entity, entity)\
    entity->InstanceName= instanceName;        \
    entity->EntityName = #__EntityName;       \
    entity->Components = T3_List_Init(20);    \
    entity->Parent=NULL;                      \
    __Body                                    \
    return entity;                            \
}

#define T3_Entity_AddComponent(__ComponentType, __VariableName, __Body) \
    T3_MallocSafe(__ComponentType,__VariableName)                       \
    __Body                                                              \
    T3_List_Add(entity->Components, T3_Comp_Init(__VariableName))

#endif //T3_ENTITY_H
