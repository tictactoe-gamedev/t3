#ifndef T3_HELPERS_H
#define T3_HELPERS_H

#include <stdlib.h>
#include "t3-types.h"
#include "config-project.h"

/** ------------------------------- LOGGING ----------------------------------- */

typedef enum {
    Info, Warning, Error
} T3_Log_Level;

void T3_Helper_Log(T3_Log_Level level, const char *filename, int lineNumber, const char *format, ...);

void T3_Helper_Error_If(bool condition, const char *filename, int lineNumber, const char *format, ...);

void T3_Helper_Assert(bool condition, const char *format, ...);

/** ------------------------------- MEMORY ----------------------------------- */

#define T3_HELPER_MALLOC(type) (type *) malloc(sizeof(type))
#define T3_HELPER_MALLOC_SAFE(type, variableName)                                                  \
type * variableName = (type *) malloc(sizeof(type));                                               \
T3_Helper_Error_If(variableName==NULL,__FILE__, __LINE__, "Malloc failed for ", variableName)


/** ------------------------------- RANDOMISATION ----------------------------------- */

bool T3_Helper_Random_Bool(void);

int T3_Helper_Random_Sign(void);

int T3_Helper_Random_Int(int min, int max);

float T3_Helper_Random_Float(float min, float max);

/** ------------------------------- COLOR ----------------------------------- */
#define T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(__color) __color.r, __color.g, __color.b, __color.a

#define T3_HELPER_SDL_COLOR_TO_PARAM_RGB(__color) __color.r, __color.g, __color.b

/** -------------------------------- FLAGS ----------------------------------- */

#define T3_HELPER_FLAG_SET_OPTION(__flag, __option)    __flag |= __option
#define T3_HELPER_FLAG_CLEAR_OPTION(__flag, __option)    __flag &= ~__option
#define T3_HELPER_FLAG_TOGGLE_OPTION(__flag, __option)    __flag ^= __option
#define T3_HELPER_FLAG_CHECK_OPTION(__flag, __options)    ((__flag) & (__options))

#endif
