#include "SDL.h"
#include "SDL_image.h"
#include "config/game-config.h"
#include "helper/logging.h"
#include "main.h" 
#include "library/data_structures/linked_list.h"
#include "library/data_structures/stack.h"

Uint64 PreviousFrameMS = 0;
Uint64 CurrentFrameMS = 0;
SDL_Color DefaultBackground = GAME_CONFIG_DEFAULT_BACKGROUND;

void T3_Test_LinkedList();
void T3_Test_Stack();

//Initialize SDL Libraries
void T3_Init();
void T3_GameLoop();
void T3_Destroy();

int main(int argc, char *args[]) {
    T3_Test_Stack();
    T3_Init();    
    T3_GameLoop();
    T3_Destroy();
}

void T3_Init(){
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

    SDL_SetRenderDrawColor(MainRenderer,
                           DefaultBackground.r,
                           DefaultBackground.g,
                           DefaultBackground.b,
                           DefaultBackground.a);
}

void T3_GameLoop(){
    SDL_Event e;
    bool quit= false;

    while (!quit){
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
                quit= true;
            }
        }

        SDL_RenderPresent(MainRenderer);
        PreviousFrameMS = CurrentFrameMS;
    }
}

void T3_Destroy(){
    SDL_DestroyRenderer(MainRenderer);
    SDL_DestroyWindow(MainWindow);
    IMG_Quit();
    SDL_Quit();
}

void T3_Test_LinkedList(){
    T3_LinkedList* list = T3_LinkedList_Init();
    
    T3_LinkedList_AddToHead(list,T3_Node_Init(2));
    T3_LinkedList_AddToHead(list,T3_Node_Init(5));
    T3_Log(LOG_LEVEL_INFO,list);
    
    T3_LinkedList_RemoveAt(list,0);
    T3_Node* node = T3_LinkedList_GetNode(list,0);
    int index = T3_LinkedList_FindIndexOf(list,node);
    T3_Log(LOG_LEVEL_INFO,"Found Index: %d",index);
    
    T3_LinkedList_AddToTail(list, T3_Node_Init(23));
    T3_Log(LOG_LEVEL_INFO,list);

    T3_LinkedList_AddNode(list, T3_Node_Init(-12),1);
    
    T3_LinkedList_Remove(list,node);
    T3_Node_Destroy(node);
}

void T3_Test_Stack() {
    T3_Stack* stack = T3_Stack_Init();
    T3_Stack_Push(stack, T3_Node_Init(1));
    T3_Node* node = T3_Stack_Pop(stack);
    T3_Log(LOG_LEVEL_INFO,stack);
    T3_Stack_Push(stack, T3_Node_Init(2));
    T3_Stack_Push(stack, T3_Node_Init(3));
    T3_Log(LOG_LEVEL_INFO,stack);
    T3_Stack_Push(stack, T3_Node_Init(3));
    T3_Stack_Pop(stack);
    T3_Log(LOG_LEVEL_INFO,stack);

    T3_Stack_Destroy(stack);
    
}
