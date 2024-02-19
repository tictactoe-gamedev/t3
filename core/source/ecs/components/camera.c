#include "helpers.h"
#include "ecs.h"

void T3C_Camera_OnDestroy(T3_Component *self);

void T3C_Camera_OnAddComponent(T3_Component *self);

T3_Component *T3C_Camera_Init() {
    T3_HELPER_MALLOC_SAFE(T3C_Camera, camera);
    camera->PixelPosition.x = T3_Globals_Get()->Resolution.Width / 2;
    camera->PixelPosition.y = T3_Globals_Get()->Resolution.Height / 2;
    camera->ScenePosition = NULL;

    T3_Component *component = T3_Component_Init(true);
    component->Type = T3C_TYPE_CAMERA;
    component->OnAddComponent = T3C_Camera_OnAddComponent;
    component->OnDestroy = T3C_Camera_OnDestroy;
    component->Data = camera;

    return component;
}

void T3C_Camera_OnDestroy(T3_Component *self) {
    free(self->Data);
    free(self);
}

void T3C_Camera_OnAddComponent(T3_Component *self) {
    T3_Component *positionComp = T3_Entity_GetComponent(self->Owner, T3C_TYPE_POSITION);
    T3_HELPER_ERROR_IF(positionComp == NULL, "Can't add a camera without a position component!");

    T3C_Camera *camera = (T3C_Camera *) self->Data;
    camera->ScenePosition = (T3C_Position *) positionComp->Data;
}