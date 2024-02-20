#include "helpers.h"
#include "ecs.h"

T3_ECS_GameLoop *__gameLoopRef;

T3_Entity *T3_Entity_Init(const char *name, T3_Entity *parent, T3_List *children, T3_List *components, bool isEnabled) {
    uint componentCount;
    T3_HELPER_MALLOC_SAFE(T3_Entity, entity);
    entity->Name = name;
    entity->Parent = parent;
    entity->Children = children;
    entity->Components = components;
    entity->IsEnabled = isEnabled;
    entity->IsInLoop = false;

    componentCount = components->Size;

    if (componentCount > 0) {
        uint i;

        for (i = 0; i < componentCount; ++i) {
            T3_Component *component = T3_Entity_GetComponentAt(entity, i);
            component->Owner = entity;

            if (component->OnAddComponent != NULL) {
                T3_Queue_Enqueue(__gameLoopRef->OnAddComponent, T3_Node_Init(component));
            }
        }
    }

    return entity;
}

void T3_Entity_AddComponent(T3_Entity *entity, T3_Component *component) {
    T3_Helper_Assert(component->Owner == NULL, "Component has already owned by an entity!");

    T3_List_Add(entity->Components, component);
    component->Owner = entity;

    if (component->OnAddComponent != NULL)
        T3_Queue_Enqueue(__gameLoopRef->OnAddComponent, T3_Node_Init(component));
}

void T3_Entity_AddComponentSafe(T3_Entity *entity, T3_Component *component) {
    T3_Helper_Assert(component->Owner == NULL, "Component has already owned by an entity!");

    T3_List_AddSafe(entity->Components, component);
    component->Owner = entity;

    if (component->OnAddComponent != NULL)
        T3_Queue_Enqueue(__gameLoopRef->OnAddComponent, T3_Node_Init(component));
}

void T3_Entity_EnterGameLoop(T3_Entity *entity) {
    uint i;
    T3_Helper_Assert(entity->IsInLoop == false, "Entity is already in loop?");

    entity->IsInLoop = true;

    
    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = T3_Entity_GetComponentAt(entity, i);

        if (component->OnEnter != NULL) {
            T3_Queue_Enqueue(__gameLoopRef->OnEnter, T3_Node_Init(component));
        }
        if (component->OnLoop != NULL) {
            T3_List_Add(__gameLoopRef->OnLoop, component);
        }

        component->IsInLoop = true;
    }
}

void T3_Entity_ExitGameLoop(T3_Entity *entity) {
    uint i;
    T3_Helper_Assert(entity->IsInLoop == true, "Entity is already out of the loop?");
    
    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = T3_Entity_GetComponentAt(entity, i);

        if (component->OnExit != NULL) {
            T3_Queue_Enqueue(__gameLoopRef->OnExit, T3_Node_Init(component));
        }

        if (component->OnLoop != NULL) {
            T3_List_Remove(__gameLoopRef->OnLoop, component);
        }

        component->IsInLoop = false;
    }

    entity->IsInLoop = false;
}

void T3_Entity_RemoveComponent(T3_Component *component) {
    T3_List_Remove(component->Owner->Components, component);
    component->Owner = NULL;

    if (component->OnRemoveComponent != NULL)
        T3_Queue_Enqueue(__gameLoopRef->OnRemoveComponent, T3_Node_Init(component));
}

void T3_Entity_DestroyComponent(T3_Component *component) {
    T3_List_Remove(component->Owner->Components, component);

    if (component->OnDestroy != NULL)
        T3_Queue_Enqueue(__gameLoopRef->OnDestroy, T3_Node_Init(component));
}

void T3_Entity_Destroy(T3_Entity *entity) {
    size_t i;

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(entity->Components, i);

        if (component->OnDestroy != NULL)
            T3_Queue_Enqueue(__gameLoopRef->OnDestroy, T3_Node_Init(component));
    }

    T3_List_Destroy(entity->Components);

    for (i = 0; i < entity->Children->Size; i++) {
        T3_Entity *child = (T3_Entity *) T3_List_Get(entity->Children, i);
        T3_Entity_Destroy(child);
    }

    T3_List_Destroy(entity->Children);
    free(entity);
}

T3_Component *T3_Entity_GetComponentAt(T3_Entity *entity, uint index) {
    return (T3_Component *) T3_List_Get(entity->Components, index);
}

T3_Component *T3_Entity_GetComponent(T3_Entity *entity, T3C_Type componentType) {
    uint i;
    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(entity->Components, i);
        if (component->Type == componentType) {
            return component;
        }
    }
    return NULL;
}

void T3_Entity_Enabled(T3_Entity *entity, bool isEnabled) {
    uint i;

    if (entity->IsEnabled == isEnabled)
        return;

    entity->IsEnabled = isEnabled;

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(entity->Components, i);

        if (isEnabled && component->OnEnable != NULL) {
            T3_Queue_Enqueue(__gameLoopRef->OnEnable, T3_Node_Init(component));
        } else if (isEnabled == false && component->OnDisable != NULL) {
            T3_Queue_Enqueue(__gameLoopRef->OnDisable, T3_Node_Init(component));
        }
    }
}

void T3_Entity_SetGameLoop(T3_ECS_GameLoop *loop) {
    __gameLoopRef = loop;
}
