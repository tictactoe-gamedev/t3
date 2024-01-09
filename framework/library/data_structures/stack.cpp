#include "stack.h"
#include "helper/memory.h"
#include "config/game-config.h"

#define Below Ptr1

T3_Stack *T3_Stack_Init() {
    T3_MallocSafe(T3_Stack,stack)
    stack->Top=NULL;
    stack->Count=0;
    return stack;
}

void T3_Stack_Push(T3_Stack *stack, T3_Node *node) {
    if (stack->Count!=0){
        node->Below = stack->Top;
    }
    stack->Top=node;
    stack->Count++;
}

T3_Node *T3_Stack_Pop(T3_Stack *stack) {
    T3_Node * popped = stack->Top;
    stack->Top=stack->Top->Below;
    stack->Count--;
    return popped;
}

void T3_Stack_Destroy(T3_Stack* stack) {
    for (int i = 0; i < stack->Count; ++i) {
        T3_Node * node = T3_Stack_Pop(stack);
        T3_Node_Destroy(node);
    }
    free(stack);
}


void T3_Stack_Test() {
#ifdef GAME_RELEASE
    #if GAME_RELEASE == DEVELOPMENT
        T3_Stack* stack = T3_Stack_Init();
        T3_Stack_Push(stack, T3_Node_Init(1));
        T3_Node* node = T3_Stack_Pop(stack);
        T3_Log(LOG_LEVEL_INFO,stack);
        T3_Stack_Push(stack, T3_Node_Init(2));
        T3_Stack_Push(stack, T3_Node_Init(3));
        T3_Log(LOG_LEVEL_INFO,stack);
        T3_Stack_Push(stack, T3_Node_Init(3));
        T3_Stack_Pop(stack);
        T3_Log(LOG_LEVEL_INFO,stack);
    
        T3_Stack_Destroy(stack);
    #endif
#endif
}