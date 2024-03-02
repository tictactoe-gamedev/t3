#ifndef T3_T3_TYPES_H
#define T3_T3_TYPES_H

#include <stddef.h>
#include <stdint.h>

typedef uint64_t uint64;
typedef int64_t int64;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef uint8_t bool;
typedef unsigned char byte;

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
