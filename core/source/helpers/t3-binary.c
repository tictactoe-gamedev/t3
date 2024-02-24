#include "t3-helpers.h"

void T3_Helper_Binary_Set_Flag (uint16* value, uint16 flag) { *value |= flag; }

void T3_Helper_Binary_Clear_Flag (uint16* value, uint16 flag) { *value &= ~flag; }

void T3_Helper_Binary_Toggle_Flag (uint16* value, uint16 flag) { *value ^= flag; }

bool T3_Helper_Binary_Has_Flag (uint16* value, uint16 flag) { return *value & flag; }

