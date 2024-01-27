#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "main.h"
#include "core/helpers.h"
#include "core/globals.h"

Uint64 PreviousFrameMS = 0;
Uint64 CurrentFrameMS = 0;
T3_Globals *globals;

void T3_Init();

void T3_GameLoop();

void T3_Destroy();

int main(int argc, char *args[]) {
    T3_Init();
    T3_GameLoop();
    T3_Destroy();
}

void T3_Init() {
    globals = GetGlobals();
    srand(time(NULL));

    MainWindow = NULL;
    SDL_Surface *screenSurface = NULL;

    T3_HELPER_ERROR_IF(SDL_Init(SDL_INIT_VIDEO) < 0, "%s \n", SDL_GetError());

    MainWindow = SDL_CreateWindow(globals->Title,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  globals->Resolution.Width,
                                  globals->Resolution.Height,
                                  SDL_WINDOW_SHOWN);

    T3_HELPER_ERROR_IF(MainWindow == NULL, "%s", SDL_GetError());


    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
    T3_HELPER_ERROR_IF(MainRenderer == NULL, "%s", SDL_GetError());
    T3_HELPER_ERROR_IF(
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0,
            "Couldn't load image libraries.");

    SDL_SetRenderDrawColor(MainRenderer,
                           T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(globals->DefaultBackground));

    CONFIG_ENTRY_POINT_FUNCTION_NAME();
}

void T3_GameLoop() {
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        CurrentFrameMS = SDL_GetTicks64();
        DeltaTimeInSeconds = (CurrentFrameMS - PreviousFrameMS) / 1000.0;

        SDL_SetRenderDrawColor(MainRenderer,
                               T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(globals->DefaultBackground));

        SDL_RenderClear(MainRenderer);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderPresent(MainRenderer);
        PreviousFrameMS = CurrentFrameMS;
    }
}

void T3_Destroy() {
    SDL_DestroyRenderer(MainRenderer);
    SDL_DestroyWindow(MainWindow);
    IMG_Quit();
    SDL_Quit();
}


