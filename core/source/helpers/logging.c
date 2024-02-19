#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h> 
#include "helpers.h"
#include "config-project.h"  

const char *GetLogLevelString(T3_Log_Level logLevel);

void INTERNAL_T3_Helper_Log_Message(T3_Log_Level level, const char *filename, int lineNumber, const char* format, ...){
    if(CONFIG_MINIMUM_LOG_LEVEL>level)
        return;
    
    va_list args;
    va_start(args, format);
    printf("%s[%d]: [%s]: ", filename, lineNumber, GetLogLevelString(level));
    vprintf(format, args);
    printf("\n");
    
    if(level==Error){
        exit(-1);
    }
} 

const char *GetLogLevelString(T3_Log_Level logLevel) {
    switch (logLevel) {
        case Info:
            return "INFO";
        case Warning:
            return "WARNING";
        case Error:
            return "ERROR";
    }
}