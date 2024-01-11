#include "position.h"
#include "library/ecs/component.h"

T3_Comp_Init_Begin(T3C_Position, HasRegister, NoEnter, NoLoop, NoExit, HasDestroy, NoEnable, NoDisable)

T3_Comp_Init_End

T3_Comp_Register_Begin(T3C_Position)
    
T3_Comp_Register_End

T3_Comp_Destroy_Begin(T3C_Position)
    free(self);
T3_Comp_Destroy_End