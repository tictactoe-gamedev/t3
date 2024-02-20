#include "ecs.h"
#include "helpers.h"
#include "globals.h"

void Main(void) {
    T3_Globals *globals = T3_Globals_Get();

    SDL_Rect rect = {0, 0, 100, 100};
    T3_Vector2 anchor = {0.5f, 0.5f};

    T3_Component *scene = T3C_Scene_Init("Main Scene", 1496, 748);
    
    T3_Component *camera = T3C_Camera_Init();
    T3_Component *positionCamera = T3C_Position_Init(0, 0);
    
    T3_Component *positionExampleSprite = T3C_Position_Init(0, 0);
    T3_Component *texture = T3C_Texture_Init_With_Load(globals->MainRenderer, "project-root/tileset.png");
    T3_Component *sprite = T3C_Sprite_Init((T3C_Texture *) texture->Data, rect, anchor);
    T3_Component *spriteRenderer = T3C_SpriteRenderer_Init_With_Camera((T3C_Camera *)camera->Data);

    /** Creating Scene */
    T3_Entity *main = T3_Entity_Init(
            "Main",
            NULL,
            T3_List_Init(globals->InitialEntityCapacity - 1),
            T3_List_Init_With_Elements(1, 1, scene),
            true);


    /** Creating a camera entity */
    T3_Entity *mainCamera = T3_Entity_Init(
            "MainCamera",
            main,
            NULL,
            T3_List_Init_With_Elements(2, 2, positionCamera, camera),
            true);


    T3_Entity *exampleSprite = T3_Entity_Init(
            "Sprite",
            main,
            NULL,
            T3_List_Init_With_Elements(4, 4, positionExampleSprite, texture, sprite, spriteRenderer),
            true);


    T3_Entity_EnterGameLoop(main);
    T3_Entity_EnterGameLoop(mainCamera);
    T3_Entity_EnterGameLoop(exampleSprite);
}
