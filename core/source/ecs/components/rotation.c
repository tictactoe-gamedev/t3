#include "ecs.h"
#include "helpers.h"

void T3C_Rotation_OnDestroy(T3_Component *self);

T3_Component *T3C_Rotation_Init(float radians) {
    T3_Component *component;
    T3C_Rotation *rot = T3_Helper_Malloc_Safe(sizeof *rot, T3_FILE_LINE);
    *rot = radians;

    component = T3_Component_Init(true);
    component->Type = T3C_TYPE_ROTATION;
    component->Data = rot;
    component->OnDestroy = T3C_Rotation_OnDestroy;
    return component;
}

T3_Vector2 T3C_Rotation_As_Vector2(T3C_Rotation *rotation) {
    return T3_Vector2_Init(cos(*rotation), sin(*rotation));
}

float T3C_Rotation_As_Radians(T3C_Rotation *rotation) {
    return *rotation;
}

float T3C_Rotation_As_Degrees(T3C_Rotation *rotation) {
    return *rotation * 180.0f / T3_PI;
}

void T3C_Rotation_Set_Radians(T3C_Rotation *rotation, float radians) {
    *rotation = radians;
}

void T3C_Rotation_Set_Degrees(T3C_Rotation *rotation, float degrees) {
    *rotation = degrees * T3_PI / 180.0f;
}

void T3C_Rotation_Set_Vector2(T3C_Rotation *rotation, T3_Vector2 vector) {
    *rotation = atan2(vector.y, vector.x);
}

void T3C_Rotation_Rotate_Radians(T3C_Rotation *rotation, float radians) {
    *rotation += radians;
}

void T3C_Rotation_Rotate_Degrees(T3C_Rotation *rotation, float degrees) {
    *rotation += (degrees * T3_PI / 180.0);
}

void T3C_Rotation_Rotate_Vector2(T3C_Rotation *rotation, T3_Vector2 vector) {
    *rotation += atan2(vector.y, vector.x);
}

void T3C_Rotation_RotateAround_Point(T3C_Position *position, T3_Vector2 point, float radians) {
    
    T3_Vector2 relativePos;
    float cosTheta, sinTheta;
    cosTheta = cos(radians);
    sinTheta = sin(radians);
    relativePos = T3_Vector2_Subtract(*position, point);
    position->x = relativePos.x * cosTheta - relativePos.y * sinTheta + point.x;
    position->y = relativePos.x * sinTheta - relativePos.y * cosTheta + point.y;
}

void T3C_Rotation_OrbitAround_Point(T3C_Position *position, T3C_Rotation *rotation, T3_Vector2 point, float radians) {

    T3_Vector2 relativePos;
    float cosTheta, sinTheta;
    cosTheta = cos(radians);
    sinTheta = sin(radians);
    relativePos = T3_Vector2_Subtract(*position, point);
    position->x = relativePos.x * cosTheta - relativePos.y * sinTheta + point.x;
    position->y = relativePos.x * sinTheta - relativePos.y * cosTheta + point.y;

    *rotation += radians;
}

void T3C_Rotation_OnDestroy(T3_Component *self) {
    free(self->Data);
    free(self);
}
