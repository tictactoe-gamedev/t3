#ifndef T3_MUSHROOM_H
#define T3_MUSHROOM_H
#include "library/ecs/entity.h"
#include "components/position.h"
    
    T3_EntityHeader
    (
            Mushroom,
            {
                T3_Entity_AddComponent(T3C_Position, position, {
                    position->x = x;
                    position->y = y;
                });
            },
            int x, int y
    )
    
#endif //T3_MUSHROOM_H
