#include "core/abstract-data-types.h"
#include "core/helpers.h"

T3_Stack *T3_Stack_Init() {
    T3_HELPER_MALLOC_SAFE(T3_Stack, stack);
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
        T3_HELPER_LOG(Info, "[%d]: [%d]", i, *(int *) node->Data);
        node = node->Next;
        i++;
    }
#endif
}

void T3_Stack_Test() {
#if CONFIG_BUILD_TYPE == DEVELOPMENT
    T3_Stack *stack = T3_Stack_Init();
    T3_Stack_Push(stack, T3_Node_Init_Int(1));
    T3_Node *node = T3_Stack_Pop(stack);
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