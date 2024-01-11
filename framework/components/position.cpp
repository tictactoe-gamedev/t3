#include "position.h"
#include "library/ecs/component.h"

T3_Comp_Init_Begin(T3_Component_Position, HasRegister, NoEnter, NoLoop, NoExit, HasDestroy, NoEnable, NoDisable)
    self->x=0;
    self->y=0;
T3_Comp_Init_End

T3_Comp_Register_Begin(T3_Component_Position)
    
T3_Comp_Register_End

T3_Comp_Destroy_Begin(T3_Component_Position)
    free(self);
T3_Comp_Destroy_End