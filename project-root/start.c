#include "ecs.h"
#include "helpers.h"
#include "globals.h"

void Main() {
    T3_Globals *globals = T3_Globals_Get();
      
    /** Creating Scene */
    T3_Entity *main = T3_Entity_Init(
            "Main",
            NULL,
            T3_List_Init(globals->InitialEntityCapacity - 1),
            T3_List_Init(10),
            true);

    T3_Entity_AddComponent(main, 
                           T3C_Scene_Init(
                                   "Main Scene", 
                                   1496, 
                                   748));

    /** Creating a camera entity */
    T3_Entity *mainCamera = T3_Entity_Init(
            "MainCamera",
            main,
            NULL,
            T3_List_Init(5),
            true);
    
    T3_Entity_AddComponent(mainCamera, T3C_Position_Init(0, 0));
    T3_Entity_AddComponent(mainCamera, T3C_Camera_Init());

    T3_Entity *exampleEntityToRender = T3_Entity_Init(
            "Sprite",
            main,
            NULL,
            T3_List_Init(10),
            true);

    T3_Component *texture = T3C_Texture_Init();
    T3C_Texture_Load(globals->MainRenderer, texture->Data, "project-root/tileset.png");
    
    T3_Entity_AddComponent(exampleEntityToRender, texture);
    
    SDL_Rect rect = {0,0, 100,100};
    T3_Vector2 anchor = {0.5f, 0.5f};
    T3_Component *sprite = T3C_Sprite_Init((T3C_Texture*)texture->Data,rect,anchor);
    T3_Entity_AddComponent(exampleEntityToRender, T3C_Position_Init(0,0));
    
    T3_Entity_AddComponent(exampleEntityToRender,sprite);
    
    T3_Component * spriteRendererComp = T3C_SpriteRenderer_Init();
        
    T3C_SpriteRenderer * renderer = (T3C_SpriteRenderer *)spriteRendererComp->Data;
    renderer->Camera = T3_Entity_GetComponent(mainCamera,T3C_TYPE_CAMERA)->Data;
    T3_Entity_AddComponent(exampleEntityToRender,spriteRendererComp);
    
    
    T3_Entity_EnterGameLoop(main);
    T3_Entity_EnterGameLoop(mainCamera);
    T3_Entity_EnterGameLoop(exampleEntityToRender);
}