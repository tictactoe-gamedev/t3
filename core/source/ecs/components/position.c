#include "helpers.h"
#include "ecs.h"

void T3C_Position_OnDestroy (T3_Component *self);

T3_Component *T3C_Position_Init (float x, float y) {

    T3C_Position *pos = T3_Helper_Malloc_Safe (sizeof *pos, T3_FILE_LINE);
    T3_Component_Default (&pos->component, true);
    pos->component.Type = Position;
    pos->pos.x = x;
    pos->pos.y = y;
    pos->component.OnDestroy = T3C_Position_OnDestroy;

    return &pos->component;
}

void T3C_Position_OnDestroy (T3_Component *self) {
    free ((T3C_Position *)self);
}

T3_Vector2 T3C_Position_ToPixel (T3C_Position *position, T3C_Camera *camera) {
    T3_Vector2 sceneToPixel = T3_Vector2_Subtract (camera->PixelPosition, camera->ScenePosition->pos);
    return T3_Vector2_Add (position->pos, sceneToPixel);
}
