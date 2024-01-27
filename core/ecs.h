#ifndef T3_ECS_H
#define T3_ECS_H

#include "abstract-data-types.h"

typedef struct T3_Entity T3_Entity;
typedef struct T3_Component T3_Component;

typedef void (*T3_EntityComponentFunction)(T3_Entity *entity, T3_Component *component);

typedef void (*T3_ComponentFunction)(T3_Component *component);

struct T3_Entity {
    const char *Name;
    T3_Entity *Parent;
    T3_List *Children;
    T3_List *Components;
};

struct T3_Component {
    void *Data;
    T3_Entity *Owner;
    T3_EntityComponentFunction OnAddComponent;
    T3_ComponentFunction OnRemoveComponent;
    T3_ComponentFunction OnEnter;
    T3_ComponentFunction OnExit;
    T3_ComponentFunction OnEnable;
    T3_ComponentFunction OnDisable;
    T3_ComponentFunction OnDestroy;
    T3_ComponentFunction OnLoop;
};

typedef T3_Vector2 T3C_Position;

typedef struct T3C_Scene {
    const char *Name;
    uint Width;
    uint Height;
} T3C_Scene;

/** ------------------------------- ENTITY  ----------------------------------- */

T3_Entity *T3_Entity_Init(const char *name, T3_Entity *parent, T3_List *children, T3_List *components);

void T3_Entity_AddComponent(T3_Entity *entity, T3_Component *component);

void T3_Entity_AddComponentSafe(T3_Entity *entity, T3_Component *component);

void T3_Entity_RemoveComponent(T3_Component *component);

void T3_Entity_DestroyComponent(T3_Component *component);

void T3_Entity_Destroy(T3_Entity *entity);

/** ------------------------------- COMPONENT  ----------------------------------- */

T3_Component *T3_Component_Init();

/** ------------------------------- POSITION COMPONENT----------------------------------- */

T3_Component *T3C_Position_Init(float x, float y);

void T3C_Position_OnDestroy(T3_Component *self);

/** ------------------------------- SCENE COMPONENT----------------------------------- */

T3_Component *T3C_Scene_Init(const char *name, int width, int height);


#endif //T3_ECS_H