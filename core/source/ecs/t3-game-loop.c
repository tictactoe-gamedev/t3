#include "t3-helpers.h"
#include "t3-ecs.h"

T3_ECS_GameLoop *internal_gameLoop;


void T3_Ecs_GameLoop_Init(void) {
    T3_ECS_GameLoop *gameLoop = T3_Helper_Malloc_Safe(sizeof *gameLoop, T3_FILE_LINE);
    internal_gameLoop = gameLoop;
    internal_gameLoop->Components = T3_List_Init(50);
    T3_Entity_SetGameLoop(gameLoop);
}

void T3_Ecs_GameLoop_Step(void) {
    uint32 i;
    uint32 componentCount = internal_gameLoop->Components->Size;
    for (i = 0; i < componentCount; ++i) {
        T3_Component *comp = T3_List_Get(internal_gameLoop->Components, i);
        comp->GameLoopFunction(comp);
    }
}
