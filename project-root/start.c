#include "core/ecs.h"
#include "core/helpers.h"

void Main() {
    T3_Entity *main = T3_Entity_Init(
            "Main",
            NULL,
            T3_List_Init(1000),
            T3_List_Init(10));

    T3_Entity_AddComponent(main, T3C_Scene_Init("Main Scene", 1496, 748));
    
    
}