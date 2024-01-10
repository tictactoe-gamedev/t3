#ifndef T3_LOGGING_H
#define T3_LOGGING_H

#include <cstdlib>
#include "library/data_structures/linked_list.h"
#include "library/data_structures/stack.h"
#include "library/data_structures/queue.h"
#include "config/game-config.h"

const size_t LOG_LEVEL_INFO = 0;
const size_t LOG_LEVEL_WARNING = 1;
const size_t LOG_LEVEL_ERROR = 2;

void INTERNAL_T3_Log(size_t logLevel, const char *filename, int lineNumber, const char *message, ...);

void INTERNAL_T3_Log(size_t logLevel, const char *filename, int lineNumber, T3_LinkedList *linkedList, ...);

void INTERNAL_T3_Log(size_t logLevel, const char *filename, int lineNumber, T3_LinkedListDouble *linkedList, ...);

void INTERNAL_T3_Log(size_t logLevel, const char *filename, int lineNumber, T3_Stack *stack, ...);

void INTERNAL_T3_Log(size_t logLevel, const char *filename, int lineNumber, T3_Queue *queue, ...);

#define T3_Log(level, message, ...) \
INTERNAL_T3_Log(level, __FILE__, __LINE__, message, ## __VA_ARGS__)

#define T3_ErrorIf(condition, message, ...) \
if ((condition)) { \
    INTERNAL_T3_Log(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ##__VA_ARGS__); \
    exit(-1); \
}

#ifdef GAME_RELEASE
    #if GAME_RELEASE == DEVELOPMENT
        /**
         * If condition is TRUE, it'll halt the execution
         */
        #define T3_Assert(condition, message, ...) \
                    if ((condition)) { \
                        INTERNAL_T3_Log(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ##__VA_ARGS__); \
                        exit(-1); \
                    }
    #else
         /**
         * If condition is TRUE, it'll halt the execution
         */
        #define T3_Assert(condition, message, ...) ((void)0)
    #endif
#else
#define T3_Assert(condition, message, ...) ((void)0)
#endif

#endif //T3_LOGGING_H
