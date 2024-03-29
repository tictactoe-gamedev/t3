#include <SDL_log.h>
#include "t3-helpers.h"
#include "t3-abstract-data-types.h"

T3_Stack *T3_Stack_Init(void) {
    T3_Stack *stack = T3_Helper_Malloc_Safe(sizeof *stack, T3_FILE, T3_LINE);
    stack->Top = NULL;
    stack->Count = 0;
    return stack;
}

void T3_Stack_Push(T3_Stack *stack, T3_Node *node) {
    if (stack->Count != 0) {
        node->Next = stack->Top;
    }
    stack->Top = node;
    stack->Count++;
}

T3_Node *T3_Stack_Pop(T3_Stack *stack) {
    T3_Node *popped = stack->Top;
    stack->Top = stack->Top->Next;
    stack->Count--;
    return popped;
}

void T3_Stack_Destroy(T3_Stack *stack) {
    int i;
    for (i = 0; i < stack->Count; ++i) {
        T3_Node *node = T3_Stack_Pop(stack);
        T3_Node_Destroy(node);
    }
    free(stack);
}

void T3_Stack_Log_Int(T3_Stack *queue) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    int i = 0;
    T3_Node *node = queue->Top;
    while (node != NULL) {
        SDL_Log("%s[%d]: [%d]->[%d]", T3_FILE,T3_LINE,i, *(int *)node->Data);
        node = node->Next;
        i++;
    }
#endif
}

void T3_Stack_Test(void) {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    T3_Node *node;
    T3_Stack *stack = T3_Stack_Init();
    T3_Stack_Push(stack, T3_Node_Init_Int(1));
    node = T3_Stack_Pop(stack);
    T3_Stack_Log_Int(stack);
    T3_Stack_Push(stack, T3_Node_Init_Int(2));
    T3_Stack_Push(stack, T3_Node_Init_Int(3));
    T3_Stack_Log_Int(stack);
    T3_Stack_Push(stack, T3_Node_Init_Int(3));
    T3_Stack_Pop(stack);
    T3_Stack_Log_Int(stack);

    T3_Stack_Destroy(stack);
#endif
}
