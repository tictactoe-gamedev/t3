#include "t3-helpers.h"
#include "t3-abstract-data-types.h"

T3_Node *T3_Node_Init(void *data) {
    T3_Node *node = T3_Helper_Malloc_Safe(sizeof *node, T3_FILE_LINE);
    node->Data = data;
    node->Next = NULL;
    return node;
}

T3_NodeDouble *T3_NodeDouble_Init(void *data) {
    T3_NodeDouble *nodeDouble = T3_Helper_Malloc_Safe(sizeof *nodeDouble, T3_FILE_LINE);
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
    int *value = T3_Helper_Malloc_Safe(sizeof *value, T3_FILE_LINE);
    *value = data;
    return T3_Node_Init(value);
}

T3_Node *T3_Node_Init_Float(float data) {
    float *value = T3_Helper_Malloc_Safe(sizeof *value, T3_FILE_LINE);
    *value = data;
    return T3_Node_Init(value);
}

T3_NodeDouble *T3_NodeDouble_Init_Int(int data) {
    int *value = T3_Helper_Malloc_Safe(sizeof *value, T3_FILE_LINE);
    *value = data;
    return T3_NodeDouble_Init(value);
}

T3_NodeDouble *T3_NodeDouble_Init_Float(float data) {
    float *value = T3_Helper_Malloc_Safe(sizeof *value, T3_FILE_LINE);
    *value = data;
    return T3_NodeDouble_Init(value);
}
