#include "node.h"
#include "helper/memory.h"
#include <cstdlib>

#define T3_Node_Overload_Implementation_Primitive(__nodeType,__primitiveType)\
__nodeType * __nodeType##_Init(__primitiveType value){                         \
    T3_MallocSafe(__nodeType, node);                                       \
    __primitiveType * val = T3_Malloc(__primitiveType);                      \
    * val = value;                                                       \
    node->Data = val;                                                    \
    node->Ptr1 = NULL;                                                   \
    return node;}

T3_Node* T3_Node_Init(void* data){
    T3_MallocSafe(T3_Node, node);
    node->Data = data;
    node->Ptr1 = NULL;
    return node;
}

T3_NodeDouble* T3_NodeDouble_Init(void* data){
    T3_MallocSafe(T3_NodeDouble, nodeDouble);
    nodeDouble->Data = data;
    nodeDouble->Ptr1 = NULL;
    nodeDouble->Ptr2 = NULL;
    return nodeDouble;
}

T3_Node_Overload_Implementation_Primitive(T3_Node,int)
T3_Node_Overload_Implementation_Primitive(T3_Node,float)
T3_Node_Overload_Implementation_Primitive(T3_NodeDouble,int)
T3_Node_Overload_Implementation_Primitive(T3_NodeDouble,float)

void T3_Node_Destroy(T3_Node *node) {
    free(node->Data);
    free(node);
}

void T3_NodeDouble_Destroy(T3_NodeDouble *node) {
    free(node->Data);
    free(node);
}
