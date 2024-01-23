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


#define T3_ComponentHeader(__ComponentName, __Register, __Enter, __Loop, __Exit, __Destroy, __Enable, __Disable, __Body) \
typedef struct __ComponentName __Body __ComponentName;                                                       \
__Register(void __ComponentName##_Register(T3_Entity* entity, T3_Comp* comp);)                             \
__Enter(void __ComponentName##_Enter(T3_Comp* comp);)                                                      \
__Exit(void __ComponentName##_Exit(T3_Comp* comp);)                                                        \
__Enable(void __ComponentName##_Enable(T3_Comp* comp);)                                                    \
__Disable(void __ComponentName##_Disable(T3_Comp* comp);)                                                  \
__Destroy(void __ComponentName##_Destroy(T3_Comp* comp);)                                                  \
__Loop(void __ComponentName##_Loop(T3_Comp* comp, unsigned int loopID);)                                   \
T3_Comp* T3_Comp_Init(__ComponentName * self);                                                           \

/** 
 * Triggers when you initialize a T3_Comp with give type
 */
#define T3_Comp_Init_Begin(__ComponentName, __Register, __Enter, __Loop, __Exit, __Destroy, __Enable, __Disable)          \
T3_Comp* T3_Comp_Init(__ComponentName * self){                                                                            \
    T3_MallocSafe(T3_Comp, comp);                                                                                       \
    __Register(comp->Register = __ComponentName##_Register;)                                                              \
    __Enter(comp->Enter = __ComponentName##_Enter;)                                                                       \
    __Loop(comp->Loop = __ComponentName##_Loop;)                                                                          \
    __Exit(comp->Exit = __ComponentName##_Exit;)                                                                          \
    __Destroy(comp->Destroy = __ComponentName##_Destroy;)                                                                 \
    __Enable(comp->Enable = __ComponentName##_Enable;)                                                                    \
    __Disable(comp->Loop = __ComponentName##_Disable;)                                                                    \
    
#define T3_Comp_Init_End comp->Data = self; return comp;}

/**
 * This is triggered right before attaching a component to an entity
 * You don't need to manually add component to entity. It's handled right before the function completed
 */
#define T3_Comp_Register_Begin(__ComponentName)                                                                           \
void __ComponentName##_Register(T3_Entity* entity, T3_Comp* comp){                                                        \
__ComponentName * self = (__ComponentName *)comp->Data;

#define T3_Comp_Register_End T3_List_AddSafe(entity->Components, comp); }

/**
 * Triggers when component processed in the game loop first time 
 * (or after Exit -> Enter again)
 */
#define T3_Comp_Enter_Begin(__ComponentName)                                                                              \
void __ComponentName##_Enter(T3_Comp* comp){                                                                              \
    __ComponentName * self = (__ComponentName *)comp->Data;
                                                                                                                        
#define T3_Comp_Enter_End }

#define T3_Comp_Loop_Begin(ComponentName)                                                                              \
void ComponentName##_Loop(T3_Comp* comp, unsigned int loopID){                                                         \
    ComponentName * self = (ComponentName *)comp->Data;
    //TODO: We'll put deltatime based on the loop

#define T3_Comp_Loop_End }

#define T3_Comp_Exit_Begin(__ComponentName)                                                                              \
void __ComponentName##_Exit(T3_Comp* comp){                                                                              \
    __ComponentName * self = (__ComponentName *)comp->Data;

#define T3_Comp_Exit_End }

/**
 * Attention, Destroy has no default way to free memory. You should handle freeing 
 * (or any kind of disposal)
 */
#define T3_Comp_Destroy_Begin(__ComponentName)                                                                           \
void __ComponentName##_Destroy(T3_Comp* comp){                                                                           \
    __ComponentName * self = (__ComponentName *)comp->Data;

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