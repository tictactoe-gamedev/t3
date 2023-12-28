#include <cstdio>
#include <cstdarg>
#include "logging.h"

const char *GetLogLevelString(int logLevel);


void LogMessage(int logLevel, const char *filename, int lineNumber, const char *message, va_list args) {
    printf("%s[%d]: [%s]: ",
           filename,
           lineNumber,
           GetLogLevelString(logLevel));

    vprintf(message, args);
    printf("\n");
}


const char *GetLogLevelString(int logLevel) {
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

void __T3_Log(int logLevel, const char *filename, int lineNumber, const char *message, ...) {
    va_list args;
    va_start(args,message);
    LogMessage(logLevel, filename, lineNumber,message, args);
    va_end(args);
}
