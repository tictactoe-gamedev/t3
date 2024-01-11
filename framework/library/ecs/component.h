#ifndef T3_COMPONENT_H
#define T3_COMPONENT_H

#include "helper/memory.h"
#include "entity.h"

struct T3_Comp;
struct T3_Entity;

typedef void (*T3_EntityComponentFunc)(T3_Entity *entity, T3_Comp *comp);

typedef void (*T3_ComponentFunc)(T3_Comp *comp);

typedef void (*T3_ComponentLoopFnc)(T3_Comp *comp, unsigned int loopID);

enum T3_Comp_State{None, Initialized, Registered, Entered, Looping, Exited, Disabled, Enabled};

typedef struct T3_Comp {
    void *Data;
    T3_Comp_State State;
    T3_Entity *Entity;
    T3_EntityComponentFunc Register;
    T3_ComponentLoopFnc Loop;
    T3_ComponentFunc Enter;
    T3_ComponentFunc Exit;
    T3_ComponentFunc Enable;
    T3_ComponentFunc Disable;
    T3_ComponentFunc Destroy;
} T3_Comp;

#define HasRegister Enabled
#define NoRegister Disabled
#define HasEnter Enabled
#define NoEnter Disabled
#define HasExit Enabled
#define NoExit Disabled
#define HasEnable Enabled
#define NoEnable Disabled
#define HasDisable Enabled
#define NoDisable Disabled
#define HasDestroy Enabled
#define NoDestroy Disabled
#define HasLoop Enabled
#define NoLoop Disabled

#define Disabled(x)  
#define Enabled(x) x


#define T3_ComponentHeader(ComponentName, Register, Enter, Loop, Exit, Destroy, Enable, Disable, Body) \
typedef struct ComponentName Body ComponentName;                                                       \
Register(void ComponentName##_Register(T3_Entity* entity, T3_Comp* comp);)                             \
Enter(void ComponentName##_Enter(T3_Comp* comp);)                                                      \
Exit(void ComponentName##_Exit(T3_Comp* comp);)                                                        \
Enable(void ComponentName##_Enable(T3_Comp* comp);)                                                    \
Disable(void ComponentName##_Disable(T3_Comp* comp);)                                                  \
Destroy(void ComponentName##_Destroy(T3_Comp* comp);)                                                  \
Loop(void ComponentName##_Loop(T3_Comp* comp, unsigned int loopID);)                                   \
T3_Comp* T3_Comp_Init(ComponentName * self);                                                           \

/** 
 * Triggers when you initialize a T3_Comp with give type
 */
#define T3_Comp_Init_Begin(ComponentName, __Register, __Enter, __Loop, __Exit, __Destroy, __Enable, __Disable)          \
T3_Comp* T3_Comp_Init(ComponentName * self){                                                                            \
    T3_MallocSafe(T3_Comp, comp);                                                                                       \
    __Register(comp->Register = ComponentName##_Register;)                                                              \
    __Enter(comp->Enter = ComponentName##_Enter;)                                                                       \
    __Loop(comp->Loop = ComponentName##_Loop;)                                                                          \
    __Exit(comp->Exit = ComponentName##_Exit;)                                                                          \
    __Destroy(comp->Destroy = ComponentName##_Destroy;)                                                                 \
    __Enable(comp->Enable = ComponentName##_Enable;)                                                                    \
    __Disable(comp->Loop = ComponentName##_Disable;)                                                                    \
    
#define T3_Comp_Init_End comp->Data = self; return comp;}

/**
 * This is triggered right before attaching a component to an entity
 * You don't need to manually add component to entity. It's handled right before the function completed
 */
#define T3_Comp_Register_Begin(ComponentName)                                                                           \
void ComponentName##_Register(T3_Entity* entity, T3_Comp* comp){                                                        \
ComponentName * self = (ComponentName *)comp->Data;

#define T3_Comp_Register_End T3_List_AddSafe(entity->Components, comp); }

/**
 * Triggers when component processed in the game loop first time 
 * (or after Exit -> Enter again)
 */
#define T3_Comp_Enter_Begin(ComponentName)                                                                              \
void ComponentName##_Enter(T3_Comp* comp){                                                                              \
    ComponentName * self = (ComponentName *)comp->Data;                                                                                  
                                                                                                                        
#define T3_Comp_Enter_End }

#define T3_Comp_Loop_Begin(ComponentName)                                                                              \
void ComponentName##_Loop(T3_Comp* comp, unsigned int loopID){                                                         \
    ComponentName * self = (ComponentName *)comp->Data;
    //TODO: We'll put deltatime based on the loop

#define T3_Comp_Loop_End }

#define T3_Comp_Exit_Begin(ComponentName)                                                                              \
void ComponentName##_Exit(T3_Comp* comp){                                                                              \
    ComponentName * self = (ComponentName *)comp->Data;

#define T3_Comp_Exit_End }

/**
 * Attention, Destroy has no default way to free memory. You should handle freeing 
 * (or any kind of disposal)
 */
#define T3_Comp_Destroy_Begin(ComponentName)                                                                           \
void ComponentName##_Destroy(T3_Comp* comp){                                                                           \
    ComponentName * self = (ComponentName *)comp->Data;

#define T3_Comp_Destroy_End  }

#define T3_Comp_Enable_Begin(ComponentName)                                                                           \
void ComponentName##_Enable(T3_Comp* comp){                                                                           \
    ComponentName * self = (ComponentName *)comp->Data;

#define T3_Comp_Enable_End  }

#define T3_Comp_Disable_Begin(ComponentName)                                                                           \
void ComponentName##_Disable(T3_Comp* comp){                                                                           \
    ComponentName * self = (ComponentName *)comp->Data;

#define T3_Comp_Disable_End  }


#endif //T3_COMPONENT_H