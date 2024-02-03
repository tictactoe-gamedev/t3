#include "core/ecs.h"
#include "core/helpers.h"
#include "core/globals.h"

void Main() {
    T3_Globals * globals = T3_Globals_Get();
    
    T3_Entity *main = T3_Entity_Init(
            "Main",
            NULL,
            T3_List_Init(globals->InitialEntityCapacity-1),
            T3_List_Init(10),
            true);

    T3_Entity_AddComponent(main, T3C_Scene_Init("Main Scene", 1496, 748));
    T3_Entity_EnterGameLoop(main);
}