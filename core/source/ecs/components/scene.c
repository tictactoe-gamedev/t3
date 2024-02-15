#include "core/ecs.h"
#include "core/helpers.h"

T3_Component *T3C_Scene_Init(const char *name, int width, int height) {
    T3_HELPER_MALLOC_SAFE(T3C_Scene, scene);
    
    scene->Name = name;
    scene->Width = width;
    scene->Height = height;
    
    T3_Component *component = T3_Component_Init(true);
    component->Type = T3C_TYPE_SCENE;
    component->Data = scene;
    return component;
}

//TODO: We need a scene destroy which removes entities efficiently as batches from the scene
