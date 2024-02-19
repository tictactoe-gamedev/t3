#ifndef T3_GLOBALS_H
#define T3_GLOBALS_H

#include <SDL.h>
#include "adt.h"
#include "config-project.h"

typedef struct T3_Globals {
    const char *Title;
    T3_Config_Resolution Resolution;
    SDL_Color DefaultBackground;
    SDL_Color Black;
    uint InitialEntityCapacity;
    SDL_Renderer* MainRenderer;
} T3_Globals;

T3_Globals *T3_Globals_Get();

#endif //T3_GLOBALS_H
