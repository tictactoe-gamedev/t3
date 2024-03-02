#include "t3-helpers.h"
#include "t3-ecs.h"

void T3_Component_Default (T3_Component *component, bool isEnabled) {
    component->HasEvent = 0;
    component->IsEventReady = 0;
    component->Owner = NULL;
    component->IsEnabled = isEnabled;
}

T3_Component *T3_Component_Init (bool isEnabled) {
    T3_Component *component = T3_Helper_Malloc_Safe (sizeof *component, T3_FILE, T3_LINE);
    component->HasEvent = 0;
    component->IsEventReady = 0;
    component->Owner = NULL;
    component->IsEnabled = isEnabled;
    return component;
}
