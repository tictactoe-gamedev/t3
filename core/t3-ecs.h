#ifndef T3_T3_ECS_H
#define T3_T3_ECS_H

#include <SDL.h>
#include "t3-globals.h"
#include "t3-math.h"
#include "t3-abstract-data-types.h"

typedef struct T3_Entity T3_Entity;
typedef struct T3_Component T3_Component;
typedef void (*T3_GameLoop_Function) (T3_Component *comp);

struct T3_Entity {                                                  /* 56-byte */
    bool IsEnabled;                                                 /* 1-byte */
    bool IsInLoop;                                                  /* 1-byte */
    char Name[30];                                                  /* 30-byte */
    T3_Entity *Parent;                                              /* 8-byte */
    T3_List *Children;                                              /* 8-byte */
    T3_List *Components;                                            /* 8-byte */
};

typedef enum T3_GameLoop_Event {
    OnAddComponent = 1 << 0,
    OnRemoveComponent = 1 << 1,
    OnEnter = 1 << 2,
    OnExit = 1 << 3,
    OnEnable = 1 << 4,
    OnDisable = 1 << 5,
    OnDestroy = 1 << 6,
    OnLoop = 1 << 7
} T3_GameLoop_Event;

struct T3_Component {                                               /* 40-byte*/
    T3_Entity *Owner;                                               /* 8-byte */
    T3_GameLoop_Function GameLoopFunction;                          /* 8-byte */
    T3C_Type Type;                                                  /* 4-byte */
    unsigned char HasEvent;                                         /* 1-byte */
    unsigned char IsEventReady;                                     /* 1-byte */
    bool IsEnabled;                                                 /* 1-byte */
    bool IsInLoop;                                                  /* 1-byte */
};

typedef struct T3_ECS_GameLoop {                                    /*64-byte*/
    T3_List *Components;
} T3_ECS_GameLoop;

typedef struct T3C_Position {                                       /* 88-byte  */
    T3_Component component;                                         /* 80-byte  */
    T3_Vector2 pos;                                                 /* 8-byte   */
} T3C_Position;

typedef struct T3C_Rotation {                                       /* 84-byte */
    T3_Component component;
    float radians;
} T3C_Rotation;

typedef struct T3C_Scene {
    T3_Component component;                                         /* 80-byte  */
    char Name[20];                                                  /* 20-byte  */
    uint16 Width;                                                   /* 2-byte   */
    uint16 Height;                                                  /* 2-byte   */
} T3C_Scene;

typedef struct T3C_Camera {                                         /* 96-byte */
    T3_Component component;
    T3C_Position *ScenePosition;
    T3_Vector2 PixelPosition;
} T3C_Camera;

typedef struct T3C_Texture {
    T3_Component component;                                         /* 80- byte */
    char Path[200];                                                 /* 200-byte */
    SDL_Rect Rect;                                                  /* 16-byte  */
    SDL_Texture *Texture;                                           /* 8-byte   */
    int32 OriginalWidth;                                            /* 4-byte   */
    int32 OriginalHeight;                                           /* 4-byte   */
} T3C_Texture;

typedef struct T3C_Sprite {
    T3_Component component;                                         /* 80- byte */
    SDL_Rect Rect;                                                  /* 16-byte  */
    T3C_Texture *SourceTexture;                                     /* 8-byte   */
    T3_Vector2 AnchorPoint;                                         /* 8-byte   */
} T3C_Sprite;

typedef struct T3C_SpriteRenderer {
    T3_Component component;
    T3C_Camera *Camera;
    T3C_Position *Position;
    T3C_Sprite *Sprite;
    SDL_RendererFlip Flip;
    char Padding[4];
} T3C_SpriteRenderer;

/** ------------------------------- GAME LOOP --------------------------------- */
void T3_ECS_Initialize(void);
void T3_Ecs_GameLoop_Init (void);
void T3_Ecs_GameLoop_Step (void);

/** ------------------------------- ENTITY  ----------------------------------- */

void T3_Entity_SetGameLoop (T3_ECS_GameLoop *loop);

T3_Entity *T3_Entity_Init (const char *name30,
                           T3_Entity *parent,
                           T3_List *children,
                           T3_List *components,
                           bool isEnabled);

void T3_Entity_AddComponent (T3_Entity *entity, T3_Component *component);
void T3_Entity_AddComponentSafe (T3_Entity *entity, T3_Component *component);
T3_Component *T3_Entity_GetComponentAt (T3_Entity *entity, uint32 index);
T3_Component *T3_Entity_GetComponent (T3_Entity *entity, T3C_Type componentType);
void T3_Entity_EnterGameLoop (T3_Entity *entity);
void T3_Entity_ExitGameLoop (T3_Entity *entity);
void T3_Entity_RemoveComponent (T3_Component *component);
void T3_Entity_DestroyComponent (T3_Component *component);
void T3_Entity_Enabled (T3_Entity *entity, bool isEnabled);
void T3_Entity_Destroy (T3_Entity *entity);

/** ------------------------------- ENTITY_TEMPLATES  ----------------------------------- */

T3_Entity *T3E_Scene_Init (const char *entityName,
                           const char *sceneName,
                           uint32 width,
                           uint32 height,
                           uint32 initialChildrenCapacity,
                           uint32 extraComponentCapacity,
                           bool isEnabled,
                           T3_Entity *parent);

T3_Entity *T3E_Camera_Init (const char *entityName,
                            float posX, float posY,
                            uint32 initialChildrenCapacity,
                            uint32 extraComponentCapacity,
                            bool isEnabled,
                            T3_Entity *parent);

T3_Entity *T3E_Sprite_Init (const char *entityName,
                            SDL_Renderer *renderer,
                            T3C_Camera *renderCamera,
                            float posX, float posY,
                            const char *imagePath,
                            SDL_Rect spriteRect,
                            float anchorX, float anchorY,
                            uint32 initialChildrenCapacity,
                            uint32 extraComponentCapacity,
                            bool isEnabled,
                            T3_Entity *parent);

/** ------------------------------- COMPONENT  ----------------------------------- */
void T3_Component_Default (T3_Component *component, bool isEnabled);
T3_Component *T3_Component_Init (bool isEnabled);

/** ------------------------------- POSITION COMPONENT----------------------------------- */

T3_Component *T3C_Position_Init (float x, float y);
T3_Vector2 T3C_Position_ToPixel (T3C_Position *position, T3C_Camera *camera);

/** ------------------------------- ROTATION COMPONENT----------------------------------- */

T3_Component *T3C_Rotation_Init (float radians);
T3_Vector2 T3C_Rotation_As_Vector2 (T3C_Rotation *rotation);
float T3C_Rotation_As_Radians (T3C_Rotation *rotation);
float T3C_Rotation_As_Degrees (T3C_Rotation *rotation);
void T3C_Rotation_Set_Radians (T3C_Rotation *rotation, float radians);
void T3C_Rotation_Set_Degrees (T3C_Rotation *rotation, float degrees);
void T3C_Rotation_Set_Vector2 (T3C_Rotation *rotation, T3_Vector2 vector);
void T3C_Rotation_Rotate_Radians (T3C_Rotation *rotation, float radians);
void T3C_Rotation_Rotate_Degrees (T3C_Rotation *rotation, float degrees);
void T3C_Rotation_Rotate_Vector2 (T3C_Rotation *rotation, T3_Vector2 vector);
void T3C_Rotation_RotateAround_Point (T3C_Position *position, T3_Vector2 point, float radians);
void T3C_Rotation_OrbitAround_Point (T3C_Position *position, T3C_Rotation *rotation, T3_Vector2 point, float radians);

/** ------------------------------- SCENE COMPONENT----------------------------------- */

T3_Component *T3C_Scene_Init (const char *name20, uint16 width, uint16 height);

/** ------------------------------- CAMERA COMPONENT----------------------------------- */

T3_Component *T3C_Camera_Init (void);

/** ------------------------------- TEXTURE COMPONENT----------------------------------- */

T3_Component *T3C_Texture_Init (void);
T3_Component *T3C_Texture_Init_With_Load (SDL_Renderer *renderer, const char *path);
void T3C_Texture_Load (SDL_Renderer *renderer, T3C_Texture *texture, const char *path);
void T3C_Texture_SetSize (T3C_Texture *texture, int width, int height);

/** ------------------------------- SPRITE COMPONENT----------------------------------- */

T3_Component *T3C_Sprite_Init (T3C_Texture *texture, SDL_Rect rect, float anchorX, float anchorY);

/** ------------------------------- SPRITE RENDERER COMPONENT----------------------------------- */

T3_Component *T3C_SpriteRenderer_Init (void);
T3_Component *T3C_SpriteRenderer_Init_With_Camera (T3C_Camera *camera);

#endif 
