
## Logging 

`#include (framework/helper/logging.h)`

You can log "meaningful" messages on console with line numbers and 
file name that produced the message like this:

`T3_Log(LOG_LEVEL_INFO, "Your message that needs a %d", 123);`

Predefined log levels: 

`LOG_LEVEL_INFO `   
`LOG_LEVEL_WARNING`  
`LOG_LEVEL_ERROR`