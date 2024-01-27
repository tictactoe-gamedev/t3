#include "core/globals.h"

T3_Globals INTERNAL_globals = {
    "My Game",
    {1024, 768},
    {0,0,0,255},
    {0,0,0,255}
};

T3_Globals * GetGlobals(){
    return &INTERNAL_globals;
}