#ifndef T3_NODE_H
#define T3_NODE_H
 
typedef struct T3_Node{
    void* Data;
    T3_Node* Ptr1;
}T3_Node;

typedef struct T3_NodeDouble{
    void* Data;
    T3_NodeDouble* Ptr1;
    T3_NodeDouble* Ptr2;
}T3_NodeDouble;

T3_Node* T3_Node_Init(void* data);
T3_NodeDouble* T3_NodeDouble_Init(void* data);

void T3_Node_Destroy(T3_Node* node);
void T3_NodeDouble_Destroy(T3_NodeDouble* node);
#endif //T3_NODE_H
