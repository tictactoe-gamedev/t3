#include "ecs.h"
#include "helpers.h"
#include "globals.h"

void Main(void) {
    T3_Globals *globals = T3_Globals_Get();

    /** Creating Entities */
    T3_Entity *main, *mainCamera, *exampleSprite;

    /** Creating Scene */
    main = T3E_Scene_Init(
            "mainEntity",
            "MainScene",
            1024, 768,
            globals->InitialEntityCapacity - 1, 0,
            true, NULL);

    /** Creating a camera entity */
    mainCamera = T3E_Camera_Init(
            "MainCamera",
            0, 0,
            0, 0,
            true, NULL);

    /** Creating a sprite entity */
    exampleSprite = T3E_Sprite_Init(
            "exampleSprite",
            globals->MainRenderer,
            (T3C_Camera *)T3_Entity_GetComponent(mainCamera, Camera),
            0, 0,
            "project-root/tileset.png",
            T3_Helper_SDL_Rect_Init(0, 0, 100, 100),
            0.5f, 0.5f,
            0, 0,
            true, NULL);


    T3_Entity_EnterGameLoop(main);
    T3_Entity_EnterGameLoop(mainCamera);
    T3_Entity_EnterGameLoop(exampleSprite);
}
