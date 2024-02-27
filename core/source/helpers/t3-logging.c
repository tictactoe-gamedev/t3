#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "t3-helpers.h"
#include "t3-config-project.h"

const char *GetLogLevelString(T3_Log_Level logLevel);

void T3_Helper_Log(T3_Log_Level level, const char *filename, int lineNumber, const char *format, ...) {
    va_list args;

    if (CONFIG_MINIMUM_LOG_LEVEL > level)
        return;

    va_start(args, format);
    printf("%s[%d]: [%s]: ", filename, lineNumber, GetLogLevelString(level));
    vprintf(format, args);
    printf("\n");

    if (level == Error) {
        exit(-1);
    }
}

void T3_Helper_Error_If(bool condition, const char *filename, int lineNumber, const char *format, ...) {
    va_list args;

    if (condition == true) {
        va_start(args, format);
        printf("%s[%d]: [%s]: ", filename, lineNumber, GetLogLevelString(Error));
        vprintf(format, args);
        printf("\n");
        exit(-1);
    }
}

void T3_Helper_Assert(bool condition, const char *filename, int lineNumber, const char *format, ...) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    T3_Helper_Error_If(!condition, filename, lineNumber, format);
#endif
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
