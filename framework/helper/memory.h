#ifndef T3_MEMORY_H
#define T3_MEMORY_H

#include "helper/logging.h"

/**
 * Allocates a pointer from given type
 */
#define T3_Malloc(__type) (__type *) malloc(sizeof(__type))

/**
 * Initialize a pointer from given type and make assertion to 
 * check if allocation failed
 */
#define T3_MallocSafe(__type, __variableName)                         \
__type* __variableName = T3_Malloc(__type);                               \
T3_ErrorIf(__variableName==NULL,"Malloc failed for ", __variableName)


#endif //T3_MEMORY_H