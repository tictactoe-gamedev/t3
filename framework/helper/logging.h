#ifndef T3_LOGGING_H
#define T3_LOGGING_H

const int LOG_LEVEL_INFO = 0;
const int LOG_LEVEL_WARNING = 1;
const int LOG_LEVEL_ERROR = 2;

void __T3_Log(int logLevel, const char *filename, int lineNumber, const char *message, ...);


#define T3_Log(level, message, ...) \
__T3_Log(level, __FILE__, __LINE__, message, ## __VA_ARGS__)


#endif //T3_LOGGING_H
