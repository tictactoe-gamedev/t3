#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config/game-config.h"
#include "helper/logging.h"
#include "main.h"
#include "library/data_structures/abstract/list.h"
#include "library/ecs/entity.h"
#include "project/example-project-1/mushroom.h"

T3_Entity *MainEntity = NULL;
Uint64 PreviousFrameMS = 0;
Uint64 CurrentFrameMS = 0;
SDL_Color DefaultBackground = GAME_CONFIG_DEFAULT_BACKGROUND;

void T3_Init();

void T3_GameLoop();

void T3_Destroy();

int main(int argc, char *args[]) {

    T3_Entity *aMushroom = T3_Entity_Mushroom("mushroom", 15, 23);

    T3_Log(LOG_LEVEL_INFO, "Hello %s", aMushroom->InstanceName);

    T3_Init();
    T3_GameLoop();
    T3_Destroy();

    return 0;
}

void T3_Init() {
    MainWindow = NULL;
    SDL_Surface *screenSurface = NULL;

    T3_ErrorIf(SDL_Init(SDL_INIT_VIDEO) < 0, "%s \n", SDL_GetError())

    MainWindow = SDL_CreateWindow(GAME_CONFIG_TITLE,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  GAME_CONFIG_SCREEN_WIDTH,
                                  GAME_CONFIG_SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);

    T3_ErrorIf(MainWindow == NULL, "%s", SDL_GetError())


    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
    T3_ErrorIf(MainRenderer == NULL, "%s", SDL_GetError())

    T3_ErrorIf(
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0,
            "Couldn't load image libraries.")

    SDL_SetRenderDrawColor(MainRenderer,
                           DefaultBackground.r,
                           DefaultBackground.g,
                           DefaultBackground.b,
                           DefaultBackground.a);
}

void T3_GameLoop() {
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        CurrentFrameMS = SDL_GetTicks64();
        DeltaTimeInSeconds = (CurrentFrameMS - PreviousFrameMS) / 1000.0;

        SDL_SetRenderDrawColor(MainRenderer,
                               DefaultBackground.r,
                               DefaultBackground.g,
                               DefaultBackground.b,
                               DefaultBackground.a);

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


void T3_Entity_SetMain(T3_Entity *entity) {
    if (MainEntity == NULL){
        MainEntity = entity;
    }
}
