# Logging
**Header:** `#include "core/helpers.h"`

Handles logging & assertion. There's 3 predefined log levels in t3:

`T3_Log_Level::Info`   
`T3_Log_Level::Warning`   
`T3_Log_Level::Error`  

## Table Of Contents
* [Macros](#macros--functions)
    * [T3_HELPER_LOG](#t3_helper_log)
    * [T3_HELPER_ERROR_IF](#t3_helper_error_if)

## Macros
***
### T3_HELPER_LOG
[[ Top ^ ]](#table-of-contents)
```
T3_HELPER_LOG(level, formatString, ...)
```
* **... :** put any formatted text variable as you'd do in a printf

Logs a message on console which includes filename and line of execution and log type.

**Usage:**   
`T3_HELPER_LOG(Info, "My age is %d", 6);`   
`T3_HELPER_LOG(Warning, "Function xyz called");`

>**Tip:**    
> **CONFIG_MINIMUM_LOG_LEVEL** on **core/config-project.h** decides the
> minimum logging level. So if it is set to `Error`,  you can't see `Warning`s
> and `Info` messages. Setting it to error would be a good practice for production releases.

### T3_HELPER_ERROR_IF
[[ Top ^ ]](#table-of-contents)
```
T3_HELPER_ERROR_IF(condition, formatString, ...)
```
* **... :** put any formatted text variable as you'd do in a printf

If the condition is `true` it'll break the program with an error.

**Usage:**   
`T3_HELPER_ERROR_IF(a<7, "Value cannot be less than 7! Current:%d", a);`   

>**Tip:**    
>Difference between an `T3_HELPER_ASSERT` and `T3_HELPER_ERROR_IF` is that `T3_HELPER_ERROR_IF` works on production builds while `T3_HELPER_ASSERT` works only on development mode. 
> 


### T3_HELPER_ASSERT
[[ Top ^ ]](#table-of-contents)
```
T3_HELPER_ASSERT(condition, formatString, ...)
```
* **... :** put any formatted text variable as you'd do in a printf

Halts the execution of program if the condition is `false` and logs the message.

**Usage:**   
`T3_HELPER_ASSERT(something!=NULL, "something is Null!");`

>**Warning:**    
> Asserts only run on **development builds**.
