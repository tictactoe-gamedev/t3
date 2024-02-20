#include "helpers.h"
#include "ecs.h"

void T3C_Camera_OnDestroy(T3_Component *self);

void T3C_Camera_OnAddComponent(T3_Component *self);

T3_Component *T3C_Camera_Init(void) {
    T3_Component *component;
    T3C_Camera *camera = T3_Helper_Malloc_Safe(sizeof *camera, T3_FILE_LINE);
    camera->PixelPosition.x = T3_Globals_Get()->Resolution.Width / 2;
    camera->PixelPosition.y = T3_Globals_Get()->Resolution.Height / 2;
    camera->ScenePosition = NULL;

    component = T3_Component_Init(true);
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
    T3C_Camera *camera = (T3C_Camera *) self->Data;

    T3_Helper_Error_If(positionComp == NULL, __FILE__, __LINE__, "Can't add a camera without a position component!");
    camera->ScenePosition = (T3C_Position *) positionComp->Data;
}

T3_Entity *T3E_Camera_Init(const char *entityName,
                           float posX,
                           float posY,
                           uint initialChildrenCapacity,
                           uint extraComponentCapacity,
                           bool isEnabled,
                           T3_Entity* parent) {

    return T3_Entity_Init(
            entityName,
            parent,
            initialChildrenCapacity > 0 ? T3_List_Init(initialChildrenCapacity) : NULL,
            T3_List_Init_With_Elements(
                    2 + extraComponentCapacity,
                    2,
                    T3C_Position_Init(posX, posY),
                    T3C_Camera_Init()
            ),
            isEnabled);
}
