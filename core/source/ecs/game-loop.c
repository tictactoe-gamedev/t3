#include "core/ecs.h"
#include "core/helpers.h"

T3_ECS_GameLoop *__gameLoop;

void T3_Ecs_GameLoop_Init() {
    T3_HELPER_MALLOC_SAFE(T3_ECS_GameLoop, gameloop);
    __gameLoop = gameloop;
    __gameLoop->OnExit = T3_Queue_Init();
    __gameLoop->OnEnter = T3_Queue_Init();
    __gameLoop->OnEnable = T3_Queue_Init();
    __gameLoop->OnDisable = T3_Queue_Init();
    __gameLoop->OnDestroy = T3_Queue_Init();
    __gameLoop->OnAddComponent = T3_Queue_Init();
    __gameLoop->OnRemoveComponent = T3_Queue_Init();
    __gameLoop->OnLoop = T3_List_Init(T3_Globals_Get()->InitialEntityCapacity);
    T3_Entity_SetGameLoop(gameloop);
}

void T3_Ecs_GameLoop_Step() {
    T3_Queue *queue = __gameLoop->OnAddComponent;

    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnAddComponent(component);
    }

    queue = __gameLoop->OnEnable;
    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnEnable(component);
    }

    queue = __gameLoop->OnEnter;
    while (queue->Count > 0) {
        T3_Node *node = (T3_Node *) T3_Queue_Dequeue(queue);
        T3_Component *component = (T3_Component *) node->Data;
        component->OnEnter(component);
    }

    uint i;
    T3_List *loop = __gameLoop->OnLoop;

    queue = __gameLoop->OnDisable;
    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnDisable(component);
    }

    queue = __gameLoop->OnRemoveComponent;
    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnRemoveComponent(component);

        if (component->OnLoop != NULL) {
            T3_List_Remove(loop, component);
        }
    }

    queue = __gameLoop->OnDestroy;
    while (queue->Count > 0) {
        T3_Node *node = (T3_Node *) T3_Queue_Dequeue(queue);
        T3_Component *component = (T3_Component *) node->Data;
        component->OnDestroy(component);

        if (component->OnLoop != NULL) {
            T3_List_Remove(loop, component);
        }
    }

    for (i = 0; i < loop->Size; ++i) {
        T3_Component *component = (T3_Component *) T3_List_Get(loop, i);
        component->OnLoop(component);
    }
}