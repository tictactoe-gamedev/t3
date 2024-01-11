#ifndef T3_SCENE_H
#define T3_SCENE_H

#include "framework/library/ecs/component.h"

T3_ComponentHeader(
        T3C_Scene,
        HasRegister,
        HasEnter,NoLoop,HasExit,
        HasDestroy,
        NoEnable,NoDisable,
        {
            const char* Name;
            int Width;
            int Height;
        }
)

#endif //T3_SCENE_H
