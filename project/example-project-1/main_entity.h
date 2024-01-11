#ifndef T3_MAIN_ENTITY_H
#define T3_MAIN_ENTITY_H

#include "main.h"
#include "framework/library/ecs/entity.h"
#include "framework/components/scene.h"

T3_EntityHeader(
        MainEntity,
        {
            T3_Entity_AddComponent(T3C_Scene, scene, {
                    scene->Name = "MainScene";
                    scene->Height = 748;
                    scene->Width = 1496;    //this is x2 width of the window by scrolling test purpose
            });
                        
        }
)

#endif //T3_MAIN_ENTITY_H
