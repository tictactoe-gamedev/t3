#include "t3-math.h"

void T3_Vector2_Equals(T3_Vector2 *a, T3_Vector2 *b) {
    a->x = b->x;
    a->y = b->y;
}

void T3_Vector2_EqualsXY(T3_Vector2 *a, float x, float y) {
    a->x = x;
    a->y = y;
}

T3_Vector2 T3_Vector2_Subtract(T3_Vector2 a, T3_Vector2 b) {
    T3_Vector2 result;
    result.x = a.x-b.x;
    result.y = a.y-b.x;
    return result;
}

T3_Vector2 T3_Vector2_Add(T3_Vector2 a, T3_Vector2 b) {
    T3_Vector2 result;
    result.x = a.x+b.x;
    result.y = a.y+b.x;
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

T3_Vector2 T3_Vector2_Zero(void){
    T3_Vector2 zero = {0,0};
    return zero;
}
