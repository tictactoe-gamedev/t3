#ifndef T3_T3_GLOBALS_H
#define T3_T3_GLOBALS_H

#include <SDL.h>
#include "t3-abstract-data-types.h"
#include "t3-config-project.h"

typedef struct T3_Globals {
    const char *Title;
    T3_Config_Resolution Resolution;
    SDL_Color DefaultBackground;
    SDL_Color Black;
    size_t InitialComponentCapacity;
    SDL_Renderer* MainRenderer;
} T3_Globals;

T3_Globals *T3_Globals_Get(void);

#endif
