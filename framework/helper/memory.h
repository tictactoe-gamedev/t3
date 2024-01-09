#ifndef T3_MEMORY_H
#define T3_MEMORY_H

#include "helper/logging.h"

/**
 * Allocates a pointer from given type
 */
#define T3_Malloc(type) (type *) malloc(sizeof(type))

/**
 * Initialize a pointer from given type and make assertion to 
 * check if allocation failed
 */
#define T3_MallocSafe(type, variableName)                         \
type* variableName = T3_Malloc(type);                               \
T3_ErrorIf(variableName==NULL,"Malloc failed for ", variableName)        


#endif //T3_MEMORY_H
