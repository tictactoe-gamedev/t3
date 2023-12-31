#include <cstdio>
#include <cstdarg>
#include "logging.h"
#include "config/game-config.h"
#include "library/data_structures/queue.h"
#include "library/data_structures/stack.h"

const char *GetLogLevelString(uint logLevel);

void LogMessage(uint logLevel, const char *filename, int lineNumber, const char *message, va_list args) {
    printf("%s[%d]: [%s]: ",
           filename,
           lineNumber,
           GetLogLevelString(logLevel));

    vprintf(message, args);
    printf("\n");
}

const char *GetLogLevelString(uint logLevel) {
    switch (logLevel) {
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_WARNING:
            return "WARNING";
        case LOG_LEVEL_ERROR:
            return "ERROR";
        default:
            return "UNDEFINED";
    }
}

void INTERNAL_T3_Log(uint logLevel, const char *filename, int lineNumber, const char *message, ...) {

    if (GAME_LOGGING_LEVEL>logLevel)
        return;
    
    va_list args;
    va_start(args, message);
    LogMessage(logLevel, filename, lineNumber, message, args);
    va_end(args);

}

#define INTERNAL_T3_Log_LinkedIn_Implementation(linkedListType, nodeType, initialNodePointerName) \
void INTERNAL_T3_Log(uint logLevel, const char *filename, int lineNumber, linkedListType *list, ...) {  \
    nodeType * current = list->initialNodePointerName;                                             \
    int i=0;                                                                                             \
    while (current!=NULL){                                                                               \
        T3_Log(logLevel,"[%d] Value: %d",i,*(int*)current->Data);                                        \
        current = current->Ptr1;                                                                         \
        i++;                                                                                             \
    }                                                                                                    \
}                                                                           

INTERNAL_T3_Log_LinkedIn_Implementation(T3_LinkedList,T3_Node, Head)
INTERNAL_T3_Log_LinkedIn_Implementation(T3_LinkedListDouble,T3_NodeDouble, Head)
INTERNAL_T3_Log_LinkedIn_Implementation(T3_Queue,T3_Node, Head)
INTERNAL_T3_Log_LinkedIn_Implementation(T3_Stack,T3_Node, Top)