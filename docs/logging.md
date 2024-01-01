# Logging
**Header:** `#include "helper/logging.h"`

Handles logging & assertion. There's 3 predefined log levels in t3:

`LOG_LEVEL_INFO `   
`LOG_LEVEL_WARNING`  
`LOG_LEVEL_ERROR`

## Table Of Contents
* [Macros](#macros--functions)
    * [T3_Log](#t3_log)
    * [T3_Assert](#t3_assert)
    
## Macros
***
### T3_Log
[[ Top ^ ]](#table-of-contents)
```
T3_Log(level, message, ...)
```
* **... :** put any formatted text variable as you'd do in a printf

Logs a message on console which includes filename and line of execution and log type. 

**Usage:**   
`T3_Log(LOG_LEVEL_INFO, "My age is %d", 6);`
`T3_Log(LOG_LEVEL_INFO, "Function xyz called");`

>**Tip:**    
> **GAME_LOGGING_LEVEL** on console, **config/game-config.h** decides the 
> minimum logging level. So if it is set to LOG_LEVEL_ERROR,  you can't see warnings 
> and infos. Setting it to error would be a good practice for production release.

### T3_Assert
[[ Top ^ ]](#table-of-contents)
```
T3_Assert(condition, message, ...)
```
* **... :** put any formatted text variable as you'd do in a printf

Halts the execution of program if the condition is `true` and logs the message.

**Usage:**   
`T3_Assert(myInt==3, "Something wrong. MyInt is %d", myInt);`

>**Warning:**    
> Asserts only run on **development builds**.

>**Tip:**    
> A common usage of T3_Assert is null checks.