#include "t3-helpers.h"
#include "t3-ecs.h"

void T3C_Camera_Loop (T3_Component *self);

void T3C_Camera_OnDestroy (T3_Component *self);

void T3C_Camera_OnAddComponent (T3_Component *self);

T3_Component *T3C_Camera_Init (void) {
    T3C_Camera *camera = T3_Helper_Malloc_Safe (sizeof *camera, T3_FILE_LINE);
    camera->PixelPosition.x = T3_Globals_Get ()->Resolution.Width / 2;
    camera->PixelPosition.y = T3_Globals_Get ()->Resolution.Height / 2;
    camera->ScenePosition = NULL;
    T3_Component_Default (&camera->component, true);
    camera->component.Type = Camera;
    camera->component.GameLoopFunction = T3C_Camera_Loop;
    T3_Helper_Binary_Set_Flag (&camera->component.EventFlags, OnDestroy | OnAddComponent);

    return &camera->component;
}

void T3C_Camera_Loop (T3_Component *self) {
    if (T3_Helper_Binary_Has_Flag (&self->EventFlags, OnDestroy << 8)) {
        free ((T3C_Camera *) self);
    } else if (T3_Helper_Binary_Has_Flag (&self->EventFlags, OnAddComponent << 8)) {
        T3_Component *positionComp = T3_Entity_GetComponent (self->Owner, Position);
        T3C_Camera *camera = (T3C_Camera *) self;

        T3_Helper_Error_If (positionComp == NULL, __FILE__, __LINE__,
                            "Can't add a camera without a position component!");
        camera->ScenePosition = (T3C_Position *) positionComp;
        T3_Helper_Binary_Clear_Flag (&self->EventFlags, OnAddComponent << 8);
    }
}

void T3C_Camera_OnDestroy (T3_Component *self) {
    free ((T3C_Camera *) self);
}

void T3C_Camera_OnAddComponent (T3_Component *self) {
    T3_Component *positionComp = T3_Entity_GetComponent (self->Owner, Position);
    T3C_Camera *camera = (T3C_Camera *) self;

    T3_Helper_Error_If (positionComp == NULL, __FILE__, __LINE__, "Can't add a camera without a position component!");
    camera->ScenePosition = (T3C_Position *) positionComp;
}

T3_Entity *T3E_Camera_Init (const char *entityName,
                            float posX,
                            float posY,
                            uint32 initialChildrenCapacity,
                            uint32 extraComponentCapacity,
                            bool isEnabled,
                            T3_Entity *parent) {

    return T3_Entity_Init (
            entityName,
            parent,
            initialChildrenCapacity > 0 ? T3_List_Init (initialChildrenCapacity) : NULL,
            T3_List_Init_With_Elements (
                    2 + extraComponentCapacity,
                    2,
                    T3C_Position_Init (posX, posY),
                    T3C_Camera_Init ()
            ),
            isEnabled);
}
