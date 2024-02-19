#ifndef T3_T3_MATH_H
#define T3_T3_MATH_H

#include <math.h>

typedef struct T3_Vector2 {
    float x;
    float y;
} T3_Vector2;

void T3_Vector2_Equals(T3_Vector2 *a, T3_Vector2 *b);

void T3_Vector2_EqualsXY(T3_Vector2 *a, float x, float y);

T3_Vector2 T3_Vector2_Subtract(T3_Vector2 a, T3_Vector2 b);

T3_Vector2 T3_Vector2_Add(T3_Vector2 a, T3_Vector2 b);

float T3_Vector2_Magnitude(T3_Vector2 a);

T3_Vector2 T3_Vector2_Normalize(T3_Vector2 a);

T3_Vector2 T3_Vector2_MultiplyBy(T3_Vector2 a, float multiplier);

T3_Vector2 T3_Vector2_Zero();

#endif //T3_T3_MATH_H
