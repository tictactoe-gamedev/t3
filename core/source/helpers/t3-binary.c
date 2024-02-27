#include "t3-helpers.h"

void T3_Helper_Binary_Flag(T3_Flag_Type type, unsigned char *value, unsigned char flag) {
    if (type == Set) {
        *value |= flag;
    } else if (type == Clear) {
        *value &= ~flag;
    } else {
        *value ^= flag;
    }
}
bool T3_Helper_Binary_HasFlag(unsigned char *value, unsigned char flag){
    return (*value & flag) == flag;
}
