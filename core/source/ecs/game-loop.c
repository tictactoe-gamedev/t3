#include "helpers.h"
#include "ecs.h"

T3_ECS_GameLoop *internal_gameLoop;

void T3_Ecs_GameLoop_Init(void) {
    T3_ECS_GameLoop *gameLoop = T3_Helper_Malloc_Safe(sizeof *gameLoop, T3_FILE_LINE);
    internal_gameLoop = gameLoop;
    internal_gameLoop->OnExit = T3_Queue_Init();
    internal_gameLoop->OnEnter = T3_Queue_Init();
    internal_gameLoop->OnEnable = T3_Queue_Init();
    internal_gameLoop->OnDisable = T3_Queue_Init();
    internal_gameLoop->OnDestroy = T3_Queue_Init();
    internal_gameLoop->OnAddComponent = T3_Queue_Init();
    internal_gameLoop->OnRemoveComponent = T3_Queue_Init();
    internal_gameLoop->OnLoop = T3_List_Init(T3_Globals_Get()->InitialEntityCapacity);
    T3_Entity_SetGameLoop(gameLoop);
}

void T3_Ecs_GameLoop_Step(void) {
    uint i;
    T3_Queue *queue = internal_gameLoop->OnAddComponent;
    T3_List *loop = internal_gameLoop->OnLoop;

    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnAddComponent(component);
    }

    queue = internal_gameLoop->OnEnable;
    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnEnable(component);
    }

    queue = internal_gameLoop->OnEnter;
    while (queue->Count > 0) {
        T3_Node *node = (T3_Node *) T3_Queue_Dequeue(queue);
        T3_Component *component = (T3_Component *) node->Data;
        component->OnEnter(component);
    }

    queue = internal_gameLoop->OnDisable;
    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnDisable(component);
    }

    queue = internal_gameLoop->OnRemoveComponent;
    while (queue->Count > 0) {
        T3_Component *component = (T3_Component *) (T3_Queue_Dequeue(queue)->Data);
        component->OnRemoveComponent(component);

        if (component->OnLoop != NULL) {
            T3_List_Remove(loop, component);
        }
    }

    queue = internal_gameLoop->OnDestroy;
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
