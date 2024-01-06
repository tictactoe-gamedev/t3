#ifndef T3_LOGGING_H
#define T3_LOGGING_H

#include <cstdlib>

const uint LOG_LEVEL_INFO = 0;
const uint LOG_LEVEL_WARNING = 1;
const uint LOG_LEVEL_ERROR = 2;

void INTERNAL_T3_Log(uint logLevel, const char *filename, int lineNumber, const char *message, ...);

#define T3_Log(level, message, ...) \
INTERNAL_T3_Log(level, __FILE__, __LINE__, message, ## __VA_ARGS__)

/**
 * If condition is TRUE, it'll halt the execution
 */
#define T3_Assert(condition, message, ...) \
if((condition)){                             \
    INTERNAL_T3_Log(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ## __VA_ARGS__); \
    exit(-1);                                                    \
}
//TODO: Make assertions work only in development builds

#endif //T3_LOGGING_H
