# Memory
**Header:** `#include "helper/memory.h"`

Provides some macros for memory allocation/freeing kind of tasks

## Table Of Contents
* [Macros](#macros--functions)
    * [T3_Malloc](#t3_malloc)
    * [T3_MallocSafe](#t3_malloc_secure)

## Macros
***
### T3_Malloc
[[ Top ^ ]](#table-of-contents)
```
T3_Malloc(type)
```
Allocates `sizeof(type)` memory and cast it to `type*`

**Usage:**   
`MyStruct* ptr = T3_Malloc(MyStruct);`


### T3_MallocSafe
[[ Top ^ ]](#table-of-contents)
```
T3_MallocSafe(type, variableName) 
```
Initialize a variable with given type and name. Also check if malloc failed or not.

**Usage:**   
`T3_MallocSafe(MyStruct, myStructPtr)`

>**Wrong Usage:**    
> MyStruct* myStructPtr = T3_MallocSafe(MyStruct, myStructPtr);

>**Correct Usage:**    
> T3_MallocSafe(MyStruct, myStructPtr)

>**Tip:**    
> If you need a more obvious approach, you can use
> [T3_Malloc](#t3_malloc) and [T3_Assert](logging.md#t3_assert)
> with a null check.