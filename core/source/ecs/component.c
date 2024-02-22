#include "helpers.h"
#include "ecs.h"

void T3_Component_Default(T3_Component *component, bool isEnabled){
    component->OnDestroy = NULL;
    component->OnRemoveComponent = NULL;
    component->OnAddComponent = NULL;
    component->OnDisable = NULL;
    component->OnEnable = NULL;
    component->OnEnter = NULL;
    component->OnExit = NULL;
    component->OnLoop = NULL;
    component->Owner = NULL;
    component->IsEnabled = isEnabled;
}

T3_Component *T3_Component_Init(bool isEnabled) {
    T3_Component *component = T3_Helper_Malloc_Safe(sizeof *component, T3_FILE_LINE);
    component->OnDestroy = NULL;
    component->OnRemoveComponent = NULL;
    component->OnAddComponent = NULL;
    component->OnDisable = NULL;
    component->OnEnable = NULL;
    component->OnEnter = NULL;
    component->OnExit = NULL;
    component->OnLoop = NULL;
    component->Owner = NULL;
    component->IsEnabled = isEnabled;
    return component;
}
