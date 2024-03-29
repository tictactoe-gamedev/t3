# Memory

**Header:** `#include "core/helpers.h"`

Provides some macros for memory allocation/freeing kind of tasks

## Table Of Contents

* [Macros](#macros)
    * [T3_HELPER_MALLOC](#t3_helper_malloc)
    * [T3_HELPER_MALLOC_SAFE](#t3_helper_malloc_safe)

## Macros

***

### T3_HELPER_MALLOC

[[ Top ^ ]](#table-of-contents)

```
T3_HELPER_MALLOC(type)
```

Allocates `sizeof(type)` memory and cast it to `type*`

**Usage:**   
`MyStruct *ptr = T3_HELPER_MALLOC(MyStruct);`

### T3_HELPER_MALLOC_SAFE

[[ Top ^ ]](#table-of-contents)

```
T3_HELPER_MALLOC_SAFE(type, variableName) 
```

Initialize a variable with given type and name. Also check if malloc failed or not.

**Usage:**   
`T3_HELPER_MALLOC_SAFE(MyStruct, myStructPtr)`

> **Wrong Usage:**    
> MyStruct* myStructPtr = T3_MallocSafe(MyStruct, myStructPtr);

> **Correct Usage:**    
> T3_MallocSafe(MyStruct, myStructPtr)

> **Tip:**    
> If you need a more explicit approach, you can use
> [T3_Malloc](#t3_helper_malloc) and [T3_Assert](logging.md#t3_helper_assert) or 
> with a `NULL` check.