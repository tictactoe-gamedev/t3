#include "helpers.h"
#include "ecs.h"

void T3C_Position_OnDestroy(T3_Component *self);

T3_Component *T3C_Position_Init(float x, float y) {
    T3_Component *component;
    T3C_Position *pos = T3_Helper_Malloc_Safe(sizeof *pos, T3_FILE_LINE);
    pos->x = x;
    pos->y = y;

    component = T3_Component_Init(true);
    component->Type = Position;
    component->Data = pos;
    component->OnDestroy = T3C_Position_OnDestroy;
    return component;
}

void T3C_Position_OnDestroy(T3_Component *self) {
    free(self->Data);
    free(self);
}

T3_Vector2 T3C_Position_ToPixel(T3C_Position *position, T3C_Camera *camera) {
    T3_Vector2 sceneToPixel = T3_Vector2_Subtract(camera->PixelPosition, *(camera->ScenePosition));
    return T3_Vector2_Add(*position, sceneToPixel);
}
