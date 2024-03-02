#include "t3-helpers.h"
#include "t3-ecs.h"

void T3_Scene_Loop (T3_Component *self){}

T3_Component *T3C_Scene_Init (const char *name20, uint16 width, uint16 height) {

    T3C_Scene *scene = T3_Helper_Malloc_Safe (sizeof *scene, T3_FILE, T3_LINE);
    T3_Component_Default (&scene->component, true);
    SDL_snprintf(scene->Name,20,"%s",name20);
    scene->Width = width;
    scene->Height = height;
    scene->component.GameLoopFunction = T3_Scene_Loop;
    scene->component.Type = Scene;
    return &scene->component;
}

T3_Entity *T3E_Scene_Init (const char *entityName,
                           const char *sceneName,
                           uint32 width,
                           uint32 height,
                           uint32 initialChildrenCapacity,
                           uint32 extraComponentCapacity,
                           bool isEnabled,
                           T3_Entity *parent) {

    return T3_Entity_Init (
            entityName,
            parent,
            initialChildrenCapacity > 0 ? T3_List_Init (initialChildrenCapacity) : NULL,
            T3_List_Init_With_Elements (
                    1 + extraComponentCapacity,
                    1,
                    T3C_Scene_Init (sceneName, width, height)
            ),
            isEnabled);
}


/*TODO: We need a scene destroy which removes entities efficiently as batches from the scene*/
