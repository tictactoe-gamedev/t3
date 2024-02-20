#ifndef T3_ECS_H
#define T3_ECS_H

#include <SDL.h>
#include "globals.h"
#include "t3-math.h"
#include "adt.h"

typedef struct T3_Entity T3_Entity;
typedef struct T3_Component T3_Component;

typedef void (*T3_ComponentFunction)(T3_Component *component);

struct T3_Entity {
    const char *Name;
    T3_Entity *Parent;
    T3_List *Children;
    T3_List *Components;
    bool IsEnabled;
    bool IsInLoop;
};

struct T3_Component {
    T3C_Type Type;
    void *Data;
    T3_Entity *Owner;
    T3_ComponentFunction OnAddComponent;
    T3_ComponentFunction OnRemoveComponent;
    T3_ComponentFunction OnEnter;
    T3_ComponentFunction OnExit;
    T3_ComponentFunction OnEnable;
    T3_ComponentFunction OnDisable;
    T3_ComponentFunction OnDestroy;
    T3_ComponentFunction OnLoop;
    bool IsEnabled;
    bool IsInLoop;
};

typedef struct T3_ECS_GameLoop {
    T3_Queue *OnAddComponent;
    T3_Queue *OnRemoveComponent;
    T3_Queue *OnEnter;
    T3_Queue *OnExit;
    T3_Queue *OnEnable;
    T3_Queue *OnDisable;
    T3_Queue *OnDestroy;
    T3_List *OnLoop;
} T3_ECS_GameLoop;

typedef T3_Vector2 T3C_Position;

typedef struct T3C_Scene {
    const char *Name;
    uint Width;
    uint Height;
} T3C_Scene;

typedef struct T3C_Camera {
    T3C_Position *ScenePosition;
    T3_Vector2 PixelPosition;
} T3C_Camera;

typedef struct T3C_Texture {
    const char *Path;
    SDL_Texture *Texture;
    SDL_Rect Rect;
    int OriginalWidth;
    int OriginalHeight;
} T3C_Texture;

typedef struct T3C_Sprite {
    T3C_Texture *SourceTexture;
    SDL_Rect Rect;
    T3_Vector2 AnchorPoint;
} T3C_Sprite;

typedef struct T3C_SpriteRenderer {
    T3C_Camera *Camera;
    T3C_Position *Position;
    T3C_Sprite *Sprite;
    SDL_RendererFlip Flip;
} T3C_SpriteRenderer;

/** ------------------------------- GAME LOOP --------------------------------- */
void T3_Ecs_GameLoop_Init(void);

void T3_Ecs_GameLoop_Step(void);

/** ------------------------------- ENTITY  ----------------------------------- */
void T3_Entity_SetGameLoop(T3_ECS_GameLoop *loop);

T3_Entity *T3_Entity_Init(const char *name, T3_Entity *parent, T3_List *children, T3_List *components, bool isEnabled);

void T3_Entity_AddComponent(T3_Entity *entity, T3_Component *component);

void T3_Entity_AddComponentSafe(T3_Entity *entity, T3_Component *component);

T3_Component *T3_Entity_GetComponentAt(T3_Entity *entity, uint index);

T3_Component *T3_Entity_GetComponent(T3_Entity *entity, T3C_Type componentType);

void T3_Entity_EnterGameLoop(T3_Entity *entity);

void T3_Entity_ExitGameLoop(T3_Entity *entity);

void T3_Entity_RemoveComponent(T3_Component *component);

void T3_Entity_DestroyComponent(T3_Component *component);

void T3_Entity_Enabled(T3_Entity *entity, bool isEnabled);

void T3_Entity_Destroy(T3_Entity *entity);

/** ------------------------------- ENTITY_TEMPLATES  ----------------------------------- */

T3_Entity *T3E_Scene_Init(const char *entityName,
                          const char *sceneName,
                          uint width,
                          uint height,
                          uint initialChildrenCapacity,
                          uint extraComponentCapacity,
                          bool isEnabled,
                          T3_Entity *parent);

T3_Entity *T3E_Camera_Init(const char *entityName,
                           float posX, float posY,
                           uint initialChildrenCapacity,
                           uint extraComponentCapacity,
                           bool isEnabled,
                           T3_Entity *parent);

T3_Entity *T3E_Sprite_Init(const char *entityName,
                           SDL_Renderer *renderer,
                           T3C_Camera *renderCamera,
                           float posX, float posY,
                           const char *imagePath,
                           SDL_Rect spriteRect,
                           float anchorX, float anchorY,
                           uint initialChildrenCapacity,
                           uint extraComponentCapacity,
                           bool isEnabled,
                           T3_Entity *parent);

/** ------------------------------- COMPONENT  ----------------------------------- */

T3_Component *T3_Component_Init(bool isEnabled);

/** ------------------------------- POSITION COMPONENT----------------------------------- */

T3_Component *T3C_Position_Init(float x, float y);

T3_Vector2 T3C_Position_ToPixel(T3C_Position *position, T3C_Camera *camera);

/** ------------------------------- SCENE COMPONENT----------------------------------- */

T3_Component *T3C_Scene_Init(const char *name, uint width, uint height);

/** ------------------------------- CAMERA COMPONENT----------------------------------- */

T3_Component *T3C_Camera_Init(void);

/** ------------------------------- TEXTURE COMPONENT----------------------------------- */

T3_Component *T3C_Texture_Init(void);

T3_Component *T3C_Texture_Init_With_Load(SDL_Renderer *renderer, const char *path);

void T3C_Texture_Load(SDL_Renderer *renderer, T3C_Texture *texture, const char *path);

void T3C_Texture_SetSize(T3C_Texture *texture, int width, int height);

/** ------------------------------- SPRITE COMPONENT----------------------------------- */

T3_Component *T3C_Sprite_Init(T3C_Texture *texture, SDL_Rect rect, float anchorX, float anchorY);

/** ------------------------------- SPRITE RENDERER COMPONENT----------------------------------- */

T3_Component *T3C_SpriteRenderer_Init(void);

T3_Component *T3C_SpriteRenderer_Init_With_Camera(T3C_Camera *camera);

#endif 
