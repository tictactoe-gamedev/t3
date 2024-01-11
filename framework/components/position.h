#ifndef T3_POSITION_H
#define T3_POSITION_H

#include "library/ecs/component.h"

T3_ComponentHeader
(
    T3C_Position,
    HasRegister,
    NoEnter,NoLoop,NoExit,
    HasDestroy,NoEnable,NoDisable,
    {
        int x;
        int y;
    }
)
 

#endif //T3_POSITION_H
