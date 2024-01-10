#ifndef T3_STACK_H
#define T3_STACK_H

#include <cstdlib>
#include "node.h"


typedef struct T3_Stack {
    T3_Node *Top;
    size_t Count;
} T3_Stack;

T3_Stack *T3_Stack_Init();

void T3_Stack_Push(T3_Stack *stack, T3_Node *node);

T3_Node *T3_Stack_Pop(T3_Stack *stack);

void T3_Stack_Destroy(T3_Stack *stack);

void T3_Stack_Test();

#endif //T3_STACK_H
