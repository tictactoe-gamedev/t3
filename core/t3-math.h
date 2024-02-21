#ifndef T3_T3_MATH_H
#define T3_T3_MATH_H

#include <math.h>

typedef struct T3_Vector2 {
    float x;
    float y;
} T3_Vector2;

T3_Vector2 T3_Vector2_Init(float x, float y);

void T3_Vector2_EqualsXY(T3_Vector2 *a, float x, float y);

T3_Vector2 T3_Vector2_Subtract(T3_Vector2 a, T3_Vector2 b);

T3_Vector2 T3_Vector2_Add(T3_Vector2 a, T3_Vector2 b);

float T3_Vector2_Magnitude(T3_Vector2 a);

T3_Vector2 T3_Vector2_Normalize(T3_Vector2 a);

T3_Vector2 T3_Vector2_MultiplyBy(T3_Vector2 a, float multiplier);

T3_Vector2 T3_Vector2_Zero(void);

T3_Vector2 T3_Radians_ToVector2(float radians);

float T3_Vector2_ToRadians(T3_Vector2 vector);

float T3_Degrees_ToRadians(float degrees);

float T3_Radians_ToDegrees(float radians);

float T3_Vector2_ToDegrees(T3_Vector2 vector);

T3_Vector2 T3_Degrees_ToVector2(float degrees);


#endif 
