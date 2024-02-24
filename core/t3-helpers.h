#ifndef T3_T3_HELPERS_H
#define T3_T3_HELPERS_H

#include <stdlib.h>
#include <SDL_rect.h>
#include "t3-types.h"
#include "t3-config-project.h"

#define T3_FILE_LINE __FILE__, __LINE__

/** ------------------------------- LOGGING ----------------------------------- */

typedef enum {
    Info, Warning, Error
} T3_Log_Level;

void T3_Helper_Log (T3_Log_Level level, const char *filename, int lineNumber, const char *format, ...);
void T3_Helper_Error_If (bool condition, const char *filename, int lineNumber, const char *format, ...);
void T3_Helper_Assert (bool condition, const char *filename, int lineNumber, const char *format, ...);

/** ------------------------------- MEMORY ----------------------------------- */

void *T3_Helper_Malloc_Safe (size_t size, const char *filename, int lineNumber);
bool T3_Helper_Has_Padding (const char *structName, size_t totalSize, uint32 memberCount, ...);

/** ------------------------------- RANDOMISATION ----------------------------------- */

bool T3_Helper_Random_Bool (void);
int T3_Helper_Random_Sign (void);
int T3_Helper_Random_Int (int min, int max);
float T3_Helper_Random_Float (float min, float max);
/** ------------------------------- COLOR ----------------------------------- */

#define T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(__color) __color.r, __color.g, __color.b, __color.a
#define T3_HELPER_SDL_COLOR_TO_PARAM_RGB(__color) __color.r, __color.g, __color.b

/** -------------------------------- BINARY ----------------------------------- */

void T3_Helper_Binary_Set_Flag(uint16* value, uint16 flag);
void T3_Helper_Binary_Clear_Flag(uint16* value, uint16 flag);
void T3_Helper_Binary_Toggle_Flag(uint16* value, uint16 flag);
bool T3_Helper_Binary_Has_Flag(uint16* value, uint16 flag);

/** -------------------------------- SDL_RECT ----------------------------------- */

SDL_Rect T3_Helper_SDL_Rect_Init (int x, int y, int w, int h);

/** -------------------------------- CHAR ----------------------------------- */

/** Copies value[start_index] to value[end_index] to string starting from 0 to end_index-start_index
 *  It's an unsafe operation that can cause overflow and don't care about null terminating char
 */
void T3_Char_Assign_Unsafe (char *string, const char *value, uint32 start_index, uint32 end_index);

#endif
