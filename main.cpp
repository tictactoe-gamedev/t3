#include "SDL.h"
#include "SDL_image.h"
#include "config/game-config.h"
#include "helper/logging.h"
#include "main.h"

Uint64 PreviousFrameMS = 0;
Uint64 CurrentFrameMS = 0;

//Initialize SDL Libraries
void Init_SDL();

int main(int argc, char *args[]) {
    Init_SDL();    
}

void Init_SDL(){
    MainWindow = NULL;
    SDL_Surface *screenSurface = NULL;

    T3_Assert(SDL_Init(SDL_INIT_VIDEO) < 0, "%s \n", SDL_GetError())

    MainWindow = SDL_CreateWindow(GAME_CONFIG_TITLE,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  GAME_CONFIG_SCREEN_WIDTH,
                                  GAME_CONFIG_SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);

    T3_Assert(MainWindow == NULL, "%s", SDL_GetError())


    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
    T3_Assert(MainRenderer == NULL, "%s", SDL_GetError())

    T3_Assert(
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0,
            "Couldn't load image libraries.")

    SDL_Color DefaultBackground = GAME_CONFIG_DEFAULT_BACKGROUND;

    SDL_SetRenderDrawColor(MainRenderer,
                           DefaultBackground.r,
                           DefaultBackground.g,
                           DefaultBackground.b,
                           DefaultBackground.a);
}