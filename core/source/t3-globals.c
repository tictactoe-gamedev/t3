#include "t3-globals.h"

T3_Globals INTERNAL_globals = {
    "My Game",
    {1024, 768},
    {0,0,0,255},
    {0,0,0,255},
    250
};

T3_Globals * T3_Globals_Get(void){
    return &INTERNAL_globals;
}
