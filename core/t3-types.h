#ifndef T3_T3_TYPES_H
#define T3_T3_TYPES_H

#include <stddef.h>

typedef unsigned int uint;
typedef int bool;
typedef int T3C_Type;

#define true 1
#define false 0

#define T3C_TYPE_POSITION 2
#define T3C_TYPE_SCENE 3
#define T3C_TYPE_CAMERA 4
#define T3C_TYPE_TEXTURE 5
#define T3C_TYPE_SPRITE 6
#define T3C_TYPE_SPRITE_RENDERER 7

const char * T3_TypeOf(T3C_Type typeID);

#endif
