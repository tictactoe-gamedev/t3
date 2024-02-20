#include "helpers.h"
#include "ecs.h"

T3_Component *T3C_Scene_Init(const char *name, int width, int height) {
    T3_Component *component;
    T3C_Scene * scene = T3_Helper_Malloc_Safe(sizeof *scene, T3_FILE_LINE);
    
    scene->Name = name;
    scene->Width = width;
    scene->Height = height;
    
    component = T3_Component_Init(true);
    component->Type = T3C_TYPE_SCENE;
    component->Data = scene;
    return component;
}

/*TODO: We need a scene destroy which removes entities efficiently as batches from the scene*/
