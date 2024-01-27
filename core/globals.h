#ifndef T3_GLOBALS_H
#define T3_GLOBALS_H

#include "SDL_pixels.h"
#include "abstract-data-types.h"
#include "core/config-project.h"

typedef struct T3_Globals {
    const char *Title;
    T3_Config_Resolution Resolution;
    SDL_Color DefaultBackground;
    SDL_Color Black;
} T3_Globals;

T3_Globals *GetGlobals();

#endif //T3_GLOBALS_H
