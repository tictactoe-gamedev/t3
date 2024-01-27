#include "core/ecs.h"
#include "core/helpers.h"

T3_Entity *T3_Entity_Init(const char *name, T3_Entity *parent, T3_List *children, T3_List *components) {
    T3_HELPER_MALLOC_SAFE(T3_Entity, entity);
    entity->Name = name;
    entity->Parent = parent;
    entity->Children = children;
    entity->Components = components;
    return entity;
}

void T3_Entity_AddComponent(T3_Entity *entity, T3_Component *component) {
    T3_List_Add(entity->Components, component);
    if (component->OnAddComponent != NULL)
        component->OnAddComponent(entity, component);
}

void T3_Entity_AddComponentSafe(T3_Entity *entity, T3_Component *component) {
    T3_List_AddSafe(entity->Components, component);
    if (component->OnAddComponent != NULL)
        component->OnAddComponent(entity, component);
}

void T3_Entity_RemoveComponent(T3_Component *component) {
    T3_List_Remove(component->Owner->Components, component);
    if (component->OnRemoveComponent != NULL)
        component->OnRemoveComponent(component);
}

void T3_Entity_DestroyComponent(T3_Component *component) {
    T3_List_Remove(component->Owner->Components, component);
    
    if (component->OnDestroy != NULL)
        component->OnDestroy(component);
}

void T3_Entity_Destroy(T3_Entity *entity) {
    size_t i;

    for (i = 0; i < entity->Components->Size; ++i) {
        T3_Component *removed = (T3_Component *) T3_List_Get(entity->Components, i);

        if (removed->OnDestroy != NULL) {
            removed->OnDestroy(removed);
        }
    }

    T3_List_Destroy(entity->Components);

    for (i = 0; i < entity->Children->Size; i++) {
        T3_Entity *child = (T3_Entity *) T3_List_Get(entity->Children, i);
        T3_Entity_Destroy(child);
    }

    T3_List_Destroy(entity->Children);
    free(entity);
}
