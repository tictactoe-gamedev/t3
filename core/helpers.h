#ifndef T3_HELPERS_H
#define T3_HELPERS_H

#include "t3-types.h"
#include "config-project.h"
#include "stdlib.h"

/** ------------------------------- LOGGING ----------------------------------- */

typedef enum {
    Info, Warning, Error
} T3_Log_Level;

void INTERNAL_T3_Helper_Log_Message(T3_Log_Level level, const char *filename, int lineNumber, const char *format, ...);

/** Logs a message. Options for logLevel is Info, Warning, Error **/
#define T3_HELPER_LOG(logLevel, formatString, ...)  INTERNAL_T3_Helper_Log_Message(logLevel, __FILE__, __LINE__, formatString, ## __VA_ARGS__)

/** Halts the execution if condition is true */
#define T3_HELPER_ERROR_IF(condition, formatString, ...) \
if(condition)                                     \
    INTERNAL_T3_Helper_Log_Message(Error, __FILE__, __LINE__, formatString, ## __VA_ARGS__)

#if CONFIG_BUILD_TYPE == DEVELOPMENT
/** Halts the execution if condition is false and CONFIG_BUILD_TYPE is DEVELOPMENT */
#define T3_HELPER_ASSERT(condition, formatString, ...) T3_HELPER_ERROR_IF(!(condition), formatString, ##__VA_ARGS__)
#else
/** Halts the execution if condition is false and CONFIG_BUILD_TYPE is DEVELOPMENT */
#define T3_HELPER_ASSERT(condition, formatString, ...)
#endif


/** ------------------------------- MEMORY ----------------------------------- */

#define T3_HELPER_MALLOC(type) (type *) malloc(sizeof(type))
#define T3_HELPER_MALLOC_SAFE(type, variableName)                                                  \
type * variableName = (type *) malloc(sizeof(type));                                               \
T3_HELPER_ERROR_IF(variableName==NULL,"Malloc failed for ", variableName)


/** ------------------------------- RANDOMISATION ----------------------------------- */

bool T3_Helper_Random_Bool();

int T3_Helper_Random_Sign();

int T3_Helper_Random_Int(int min, int max);

float T3_Helper_Random_Float(float min, float max);

/** ------------------------------- COLOR ----------------------------------- */
#define T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(__color) __color.r, __color.g, __color.b, __color.a

#define T3_HELPER_SDL_COLOR_TO_PARAM_RGB(__color) __color.r, __color.g, __color.b

#endif //T3_HELPERS_H
