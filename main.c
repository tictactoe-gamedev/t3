#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include "helpers.h"
#include "globals.h"
#include "ecs.h"
#include "t3-input.h"

float DeltaTimeInSeconds = 0;
Uint64 PreviousFrameMS = 0;
Uint64 CurrentFrameMS = 0;
T3_Globals *globals;

SDL_Window *MainWindow = NULL;
SDL_Renderer *MainRenderer = NULL;

void T3_Init(void);

void T3_GameLoop(void);

void T3_Destroy(void);

int main(int argc, char *args[]) {
    T3_Init();
    T3_GameLoop();
    T3_Destroy();
}

void T3_Init(void) {
    SDL_Surface *screenSurface;
    globals = T3_Globals_Get();

    srand(time(NULL));

    MainWindow = NULL;
    screenSurface = NULL;

    T3_Helper_Error_If(SDL_Init(SDL_INIT_VIDEO) < 0, __FILE__, __LINE__, "%s \n", SDL_GetError());

    MainWindow = SDL_CreateWindow(globals->Title,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  globals->Resolution.Width,
                                  globals->Resolution.Height,
                                  SDL_WINDOW_SHOWN);

    T3_Helper_Error_If(MainWindow == NULL, __FILE__, __LINE__, "%s", SDL_GetError());


    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
    T3_Helper_Error_If(MainRenderer == NULL, __FILE__, __LINE__, "%s", SDL_GetError());
    T3_Helper_Error_If(
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0, __FILE__, __LINE__,
            "Couldn't load image libraries.");

    globals->MainRenderer = MainRenderer;
    SDL_SetRenderDrawColor(MainRenderer,
                           T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(globals->DefaultBackground));

    T3_Ecs_GameLoop_Init();
    T3_InputSystem_Init();
    CONFIG_ENTRY_POINT_FUNCTION_NAME();

}

void T3_GameLoop(void) {
    SDL_Event e;
    bool quit = false;
    
    while (!quit) {
        CurrentFrameMS = SDL_GetTicks64();
        DeltaTimeInSeconds = (CurrentFrameMS - PreviousFrameMS) / 1000.0;

        SDL_SetRenderDrawColor(MainRenderer,
                               T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(globals->DefaultBackground));

        SDL_RenderClear(MainRenderer);
        T3_InputSystem_Feed(&e);
        if (e.type == SDL_QUIT) {
            quit = true; 
        }

        T3_Ecs_GameLoop_Step();

        SDL_RenderPresent(MainRenderer);
        PreviousFrameMS = CurrentFrameMS;
    }
}

void T3_Destroy(void) {
    SDL_DestroyRenderer(MainRenderer);
    SDL_DestroyWindow(MainWindow);
    IMG_Quit();
    SDL_Quit();
}

