#include "t3-helpers.h"
#include "t3-ecs.h"

T3_ECS_GameLoop *internalGameLoopRef;

T3_Entity *T3_Entity_Init(const char *name30,
                          T3_Entity *parent,
                          T3_List *children,
                          T3_List *components,
                          bool isEnabled) {
    uint32 componentCount;
    T3_Entity *entity = T3_Helper_Malloc_Safe(sizeof *entity, T3_FILE, T3_LINE);
    SDL_snprintf(entity->Name,30,"%s",name30);
    entity->Parent = parent;
    entity->Children = children;
    entity->Components = components;
    entity->IsEnabled = isEnabled;
    entity->IsInLoop = false;

    componentCount = components->Size;

    if (componentCount > 0) {
        uint32 i;

        for (i = 0; i < componentCount; ++i) {
            T3_Component *component = T3_Entity_GetComponentAt(entity, i);
            component->Owner = entity;
            T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnAddComponent);
        }
    }

    return entity;
}

void T3_Entity_AddComponent(T3_Entity *entity, T3_Component *component) {
    SDL_assert(component->Owner == NULL);
    
    T3_List_Add(entity->Components, component);
    component->Owner = entity;

    T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnAddComponent);
}

void T3_Entity_AddComponentSafe(T3_Entity *entity, T3_Component *component) {
    SDL_assert(component->Owner == NULL);
    
    T3_List_AddSafe(entity->Components, component);
    component->Owner = entity;

    T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnAddComponent);
}

void T3_Entity_EnterGameLoop(T3_Entity *entity) {
    uint32 i;
    SDL_assert(entity->IsInLoop == false);
    
    entity->IsInLoop = true;

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = T3_Entity_GetComponentAt(entity, i);
        T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnEnter );
        T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnLoop );
        T3_List_Add(internalGameLoopRef->Components, component);
        component->IsInLoop = true;
    }
}

void T3_Entity_ExitGameLoop(T3_Entity *entity) {
    uint32 i;
    SDL_assert(entity->IsInLoop );

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = T3_Entity_GetComponentAt(entity, i);
        T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnExit);
        T3_Helper_Binary_Flag(Clear,&component->IsEventReady, OnLoop);

        component->IsInLoop = false;
    }

    entity->IsInLoop = false;
}

void T3_Entity_RemoveComponent(T3_Component *component) {
    T3_List_Remove(component->Owner->Components, component);
    component->Owner = NULL;

    T3_Helper_Binary_Flag(Set, &component->IsEventReady, OnRemoveComponent );
}

void T3_Entity_DestroyComponent(T3_Component *component) {
    T3_List_Remove(component->Owner->Components, component);

    T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnDestroy);
}

void T3_Entity_Destroy(T3_Entity *entity) {
    size_t i;

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(entity->Components, i);
        T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnDestroy );
    }

    T3_List_Destroy(entity->Components);

    for (i = 0; i < entity->Children->Size; i++) {
        T3_Entity *child = (T3_Entity *) T3_List_Get(entity->Children, i);
        T3_Entity_Destroy(child);
    }

    T3_List_Destroy(entity->Children);
    free(entity);
}

T3_Component *T3_Entity_GetComponentAt(T3_Entity *entity, uint32 index) {
    return (T3_Component *) T3_List_Get(entity->Components, index);
}

T3_Component *T3_Entity_GetComponent(T3_Entity *entity, T3C_Type componentType) {
    uint32 i;
    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(entity->Components, i);
        if (component->Type == componentType) {
            return component;
        }
    }
    return NULL;
}

void T3_Entity_Enabled(T3_Entity *entity, bool isEnabled) {
    uint32 i;

    if (entity->IsEnabled == isEnabled)
        return;

    entity->IsEnabled = isEnabled;

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(entity->Components, i);

        if (isEnabled)
            T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnEnable );
        else
            T3_Helper_Binary_Flag(Set,&component->IsEventReady, OnDisable );
    }
}

void T3_Entity_SetGameLoop(T3_ECS_GameLoop *loop) {
    internalGameLoopRef = loop;
}
