#ifndef T3_ENTITY_H
#define T3_ENTITY_H

#include "library/data_structures/list.h"

typedef struct T3_Entity {
    const char *EntityName;
    char * InstanceName;
    T3_List *Components;
    T3_Entity *Parent;
    T3_List *Children;
} T3_Entity;


#endif //T3_ENTITY_H
