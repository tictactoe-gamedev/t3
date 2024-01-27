#include "core/ecs.h"
#include "core/helpers.h"

T3_Component *T3C_Position_Init(float x, float y) {
    T3_HELPER_MALLOC_SAFE(T3C_Position, data);
    data->x = x;
    data->y = y;

    T3_Component *component = T3_Component_Init();
    component->Data = data;
    component->OnDestroy = T3C_Position_OnDestroy;
    return component;
}

void T3C_Position_OnDestroy(T3_Component *self) {
    free(self->Data);
    free(self);
}