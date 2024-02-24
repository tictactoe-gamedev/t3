#include "t3-ecs.h"
#include "t3-helpers.h"

void T3C_Rotation_OnDestroy (T3_Component *self);
void T3C_Rotation_Loop (T3_Component *self);

T3_Component *T3C_Rotation_Init (float radians) {
    T3C_Rotation *rot = T3_Helper_Malloc_Safe (sizeof *rot, T3_FILE_LINE);
    rot->radians = radians;
    T3_Component_Default (&rot->component, true);
    rot->component.Type = Rotation;
    rot->component.GameLoopFunction = T3C_Rotation_Loop;
    T3_Helper_Binary_Set_Flag (&rot->component.EventFlags, OnDestroy);
    return &rot->component;
}

void T3C_Rotation_Loop (T3_Component *self) {
    if (T3_Helper_Binary_Has_Flag (&self->EventFlags, OnDestroy << 8)) {
        free ((T3C_Rotation *) self);
    }
}

T3_Vector2 T3C_Rotation_As_Vector2 (T3C_Rotation *rotation) {
    return T3_Vector2_Init (cos (rotation->radians), sin (rotation->radians));
}

float T3C_Rotation_As_Radians (T3C_Rotation *rotation) {
    return rotation->radians;
}

float T3C_Rotation_As_Degrees (T3C_Rotation *rotation) {
    return rotation->radians * 180.0f / T3_PI;
}

void T3C_Rotation_Set_Radians (T3C_Rotation *rotation, float radians) {
    rotation->radians = radians;
}

void T3C_Rotation_Set_Degrees (T3C_Rotation *rotation, float degrees) {
    rotation->radians = degrees * T3_PI / 180.0f;
}

void T3C_Rotation_Set_Vector2 (T3C_Rotation *rotation, T3_Vector2 vector) {
    rotation->radians = atan2 (vector.y, vector.x);
}

void T3C_Rotation_Rotate_Radians (T3C_Rotation *rotation, float radians) {
    rotation->radians += radians;
}

void T3C_Rotation_Rotate_Degrees (T3C_Rotation *rotation, float degrees) {
    rotation->radians += (degrees * T3_PI / 180.0);
}

void T3C_Rotation_Rotate_Vector2 (T3C_Rotation *rotation, T3_Vector2 vector) {
    rotation->radians += atan2 (vector.y, vector.x);
}

void T3C_Rotation_RotateAround_Point (T3C_Position *position, T3_Vector2 point, float radians) {

    T3_Vector2 relativePos;
    float cosTheta, sinTheta;
    cosTheta = cos (radians);
    sinTheta = sin (radians);
    relativePos = T3_Vector2_Subtract (position->pos, point);
    position->pos.x = relativePos.x * cosTheta - relativePos.y * sinTheta + point.x;
    position->pos.y = relativePos.x * sinTheta - relativePos.y * cosTheta + point.y;
}

void T3C_Rotation_OrbitAround_Point (T3C_Position *position, T3C_Rotation *rotation, T3_Vector2 point, float radians) {

    T3_Vector2 relativePos;
    float cosTheta, sinTheta;
    cosTheta = cos (radians);
    sinTheta = sin (radians);
    relativePos = T3_Vector2_Subtract (position->pos, point);
    position->pos.x = relativePos.x * cosTheta - relativePos.y * sinTheta + point.x;
    position->pos.y = relativePos.x * sinTheta - relativePos.y * cosTheta + point.y;

    rotation->radians += radians;
}

void T3C_Rotation_OnDestroy (T3_Component *self) {
    free ((T3C_Rotation *) self);
}
