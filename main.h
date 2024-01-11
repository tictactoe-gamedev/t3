#ifndef T3_MAIN_H
#define T3_MAIN_H

#include "SDL.h"
#include "SDL_video.h"
#include "library/ecs/entity.h"

/** 
 * Anything that should be globally reachable from the game loop should be here
 */
 
void T3_Entity_SetMain(T3_Entity* entity);
SDL_Window* MainWindow = NULL;
SDL_Renderer* MainRenderer = NULL;

float DeltaTimeInSeconds = 0;


#endif //T3_MAIN_H
