#include "core/abstract-data-types.h"
#include "core/helpers.h"

T3_Node *T3_Node_Init(void *data) {
    T3_HELPER_MALLOC_SAFE(T3_Node, node);
    node->Data = data;
    node->Next = NULL;
    return node;
}

T3_NodeDouble *T3_NodeDouble_Init(void *data) {
    T3_HELPER_MALLOC_SAFE(T3_NodeDouble, nodeDouble);
    nodeDouble->Data = data;
    nodeDouble->Next = NULL;
    nodeDouble->Prev = NULL;
    return nodeDouble;
}

void T3_Node_Destroy(T3_Node *node) {
    free(node->Data);
    free(node);
}

void T3_NodeDouble_Destroy(T3_NodeDouble *node) {
    free(node->Data);
    free(node);
}

T3_Node *T3_Node_Init_Int(int data) {
    T3_HELPER_MALLOC_SAFE(int, value);
    *value = data;
    return T3_Node_Init(value);
}

T3_Node *T3_Node_Init_Float(float data) {
    T3_HELPER_MALLOC_SAFE(float, value);
    *value = data;
    return T3_Node_Init(value);
}

T3_NodeDouble *T3_NodeDouble_Init_Int(int data) {
    T3_HELPER_MALLOC_SAFE(int, value);
    *value = data;
    return T3_NodeDouble_Init(value);
}

T3_NodeDouble *T3_NodeDouble_Init_Float(float data) {
    T3_HELPER_MALLOC_SAFE(float, value);
    *value = data;
    return T3_NodeDouble_Init(value);
}