#include "t3-math.h"
#include "t3-types.h"

T3_Vector2 T3_Vector2_Init(float x, float y)
{
    T3_Vector2 vector2;
    vector2.x=x;
    vector2.y=y;
    return vector2;
}

void T3_Vector2_EqualsXY(T3_Vector2 *a, float x, float y) {
    a->x = x;
    a->y = y;
}

T3_Vector2 T3_Vector2_Subtract(T3_Vector2 a, T3_Vector2 b) {
    T3_Vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

T3_Vector2 T3_Vector2_Add(T3_Vector2 a, T3_Vector2 b) {
    T3_Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

float T3_Vector2_Magnitude(T3_Vector2 a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

T3_Vector2 T3_Vector2_Normalize(T3_Vector2 a) {
    float magnitude = T3_Vector2_Magnitude(a);

    if (magnitude == 0) {
        a.x = 0;
        a.y = 0;
    } else {
        a.x = a.x / magnitude;
        a.y = a.y / magnitude;
    }

    return a;
}

T3_Vector2 T3_Vector2_MultiplyBy(T3_Vector2 a, float multiplier) {
    a.x = a.x * multiplier;
    a.y = a.y * multiplier;
    return a;
}

T3_Vector2 T3_Vector2_Zero(void) {
    T3_Vector2 zero = {0, 0};
    return zero;
}

T3_Vector2 T3_Radians_ToVector2(float radians) {
    return T3_Vector2_Init(cos(radians), sin(radians));
}

float T3_Vector2_ToRadians(T3_Vector2 vector) {
    return atan2(vector.y, vector.x);
}

float T3_Degrees_ToRadians(float degrees) {
    return degrees * T3_PI / 180.0;
}

float T3_Radians_ToDegrees(float radians) {
    return radians * 180.0 / T3_PI;
}

float T3_Vector2_ToDegrees(T3_Vector2 vector) {
    return atan2(vector.y,vector.x) * 180.0 / T3_PI;
}

T3_Vector2 T3_Degrees_ToVector2(float degrees) {
    degrees = degrees * T3_PI / 180.0;
    return T3_Vector2_Init(cos(degrees), sin(degrees));
}



