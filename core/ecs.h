#ifndef T3_ECS_H
#define T3_ECS_H

#include "abstract-data-types.h"
#include "globals.h"

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

/** ------------------------------- GAME LOOP --------------------------------- */
void T3_Ecs_GameLoop_Init();

void T3_Ecs_GameLoop_Step();

/** ------------------------------- ENTITY  ----------------------------------- */
void T3_Entity_SetGameLoop(T3_ECS_GameLoop *loop);

T3_Entity *T3_Entity_Init(const char *name, T3_Entity *parent, T3_List *children, T3_List *components, bool isEnabled);

void T3_Entity_AddComponent(T3_Entity *entity, T3_Component *component);

void T3_Entity_AddComponentSafe(T3_Entity *entity, T3_Component *component);

T3_Component *T3_Entity_GetComponentAt(T3_Entity *entity, uint index);

void T3_Entity_EnterGameLoop(T3_Entity *entity);

void T3_Entity_ExitGameLoop(T3_Entity *entity);

void T3_Entity_RemoveComponent(T3_Component *component);

void T3_Entity_DestroyComponent(T3_Component *component);

void T3_Entity_Enabled(T3_Entity *entity, bool isEnabled);

void T3_Entity_Destroy(T3_Entity *entity);

/** ------------------------------- COMPONENT  ----------------------------------- */

T3_Component *T3_Component_Init(bool isEnabled);

/** ------------------------------- POSITION COMPONENT----------------------------------- */

T3_Component *T3C_Position_Init(float x, float y);

void T3C_Position_OnDestroy(T3_Component *self);

/** ------------------------------- SCENE COMPONENT----------------------------------- */

T3_Component *T3C_Scene_Init(const char *name, int width, int height);

#endif //T3_ECS_H