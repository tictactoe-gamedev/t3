#include "helpers.h"
#include "ecs.h"

T3_Component *T3C_Scene_Init (const char *name, uint width, uint height) {

    T3C_Scene *scene = T3_Helper_Malloc_Safe (sizeof *scene, T3_FILE_LINE);
    T3_Component_Default (&scene->component, true);
    scene->Name = name;
    scene->Width = width;
    scene->Height = height;

    scene->component.Type = Scene;
    return &scene->component;
}

T3_Entity *T3E_Scene_Init (const char *entityName,
                           const char *sceneName,
                           uint width,
                           uint height,
                           uint initialChildrenCapacity,
                           uint extraComponentCapacity,
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
