#include "SDL.h"
#include "config/game-config.h"
#include "helper/logging.h"
#include "main.h"

Uint64  PreviousFrameMS = 0;
Uint64  CurrentFrameMS = 0;

int main(int argc, char *args[]) {
    
    MainWindow = NULL;
    SDL_Surface *screenSurface = NULL;

    T3_Assert(SDL_Init(SDL_INIT_VIDEO)<=0, "%s \n", SDL_GetError());

    MainWindow = SDL_CreateWindow(GAME_CONFIG_TITLE,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  GAME_CONFIG_SCREEN_WIDTH,
                                  GAME_CONFIG_SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);

    T3_Assert(MainWindow == NULL, "%s", SDL_GetError() );
    
    
    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
    T3_Assert(MainRenderer == NULL, "%s", SDL_GetError());
    
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        
        
        
        if (MainWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            //Get window surface
            //screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            //SDL_UpdateWindowSurface(window);

            //Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; }}
        }

        
        //Destroy window
        //SDL_DestroyWindow(window);

        //Quit SDL subsystems
        SDL_Quit();
        
        return 0;
    }

}