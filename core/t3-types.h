#ifndef T3_T3_TYPES_H
#define T3_T3_TYPES_H

#include <stddef.h>

typedef unsigned int uint;
typedef int bool;

typedef enum T3C_Type {
    Position,
    Rotation,
    Scene,
    Camera,
    Texture,
    Sprite,
    SpriteRenderer
} T3C_Type;

#define T3_PI        3.14159265358979323846    /* pi */

#define true 1
#define false 0

#endif
