#include "node.h"
#include "helper/memory.h"
#include <cstdlib>

T3_Node* T3_Node_Init(void* data){
    T3_MallocSecure(T3_Node,node);
    node->Data = data;
    node->Ptr1 = NULL;
    return node;
}

T3_NodeDouble* T3_NodeDouble_Init(void* data){
    T3_MallocSecure(T3_NodeDouble,nodeDouble);
    nodeDouble->Data = data;
    nodeDouble->Ptr1 = NULL;
    nodeDouble->Ptr2 = NULL;
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
