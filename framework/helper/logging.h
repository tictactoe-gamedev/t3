#ifndef T3_LOGGING_H
#define T3_LOGGING_H

const int LOG_LEVEL_INFO = 0;
const int LOG_LEVEL_WARNING = 1;
const int LOG_LEVEL_ERROR = 2;

void __T3_Log(int logLevel, const char *filename, int lineNumber, const char *message, ...);


#define T3_Log(level, message, ...) \
__T3_Log(level, __FILE__, __LINE__, message, ## __VA_ARGS__)

#define T3_Assert(condition, message, ...) \
if((condition)){                             \
    __T3_Log(LOG_LEVEL_ERROR, __FILE__, __LINE__, message, ## __VA_ARGS__); \
    exit(-1);                                                    \
}\

#endif //T3_LOGGING_H
