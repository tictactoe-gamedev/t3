#include "core/ecs.h"
#include "core/helpers.h"

T3_Component *T3_Component_Init() {
    T3_HELPER_MALLOC_SAFE(T3_Component, component);
    component->OnDestroy = NULL;
    component->OnRemoveComponent = NULL;
    component->OnAddComponent = NULL;
    component->OnDisable = NULL;
    component->OnEnable = NULL;
    component->OnEnter = NULL;
    component->OnExit = NULL;
    component->Owner = NULL;
    component->Data = NULL;
    return component;
}