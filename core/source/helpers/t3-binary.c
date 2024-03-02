#include "t3-helpers.h"

void T3_Helper_Binary_Flag(T3_Flag_Type type, byte *value, byte flag) {
    if (type == Set) {
        *value |= flag;
    } else if (type == Clear) {
        *value &= ~flag;
    } else {
        *value ^= flag;
    }
}
bool T3_Helper_Binary_HasFlag(byte value, byte flag){
    return (value & flag) == flag;
}

unsigned char T3_Helper_Binary_Mask(byte value, byte mask){
    return value & mask;
}

char *T3_Helper_Binary_ToString(byte num) {
    size_t j;
    char *binary = SDL_malloc(sizeof *binary * 9);
    binary[8] = '\0';

    for (j = 0; j < 8; ++j) {
        binary[7 - j] = ((num >> j) & 1) ? '1' : '0';
    }

    return binary;
}
