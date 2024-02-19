# Randomization

**Header:** `#include "core/helpers.h"`

Provides some functions for random value production

## Table Of Contents

* [Functions](#macros)
    * [T3_Helper_Random_Bool](#t3_helper_random_bool)
    * [T3_Helper_Random_Sign](#t3_helper_random_sign)

## Macros

***

### T3_Helper_Random_Bool

[[ Top ^ ]](#table-of-contents)

```
T3_Helper_Random_Bool();
```

Randomly picks a bool value.

**Usage:**   
`bool a = T3_Helper_Random_Bool();`

### T3_Helper_Random_Sign

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