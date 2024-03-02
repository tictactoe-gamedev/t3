#ifndef T3_T3_HELPERS_H
#define T3_T3_HELPERS_H

#include <stdlib.h>
#include <SDL_rect.h>
#include "t3-types.h"
#include "t3-config-project.h"

#define T3_FILE __FILE__
#define T3_LINE __LINE__

/** ------------------------------- MEMORY ----------------------------------- */

void *T3_Helper_Malloc_Safe(size_t size, const char *filename, int lineNumber);
bool T3_Helper_Has_Padding(const char *structName, size_t totalSize, uint32 memberCount, ...);

/** ------------------------------- RANDOMISATION ----------------------------------- */

bool T3_Helper_Random_Bool(void);
int T3_Helper_Random_Sign(void);
int T3_Helper_Random_Int(int min, int max);
float T3_Helper_Random_Float(float min, float max);

/** ------------------------------- COLOR ----------------------------------- */

#define T3_HELPER_SDL_COLOR_TO_PARAM_RGBA(__color) __color.r, __color.g, __color.b, __color.a
#define T3_HELPER_SDL_COLOR_TO_PARAM_RGB(__color) __color.r, __color.g, __color.b

/** -------------------------------- HEX ----------------------------------- */

#define t3_hex_0000  0
#define t3_hex_0001  1
#define t3_hex_0010  2
#define t3_hex_0011  3
#define t3_hex_0100  4
#define t3_hex_0101  5
#define t3_hex_0110  6
#define t3_hex_0111  7
#define t3_hex_1000  8
#define t3_hex_1001  9
#define t3_hex_1010  A
#define t3_hex_1011  B
#define t3_hex_1100  C
#define t3_hex_1101  D
#define t3_hex_1110  E
#define t3_hex_1111  F

#define INTERNAL_TO_HEX(pre,a,b) pre##a##b
#define T3_HELPER_HEX(high_nibble,low_nibble) INTERNAL_TO_HEX(0x,high_nibble,low_nibble)

/** -------------------------------- BINARY ----------------------------------- */
#define t3_bits_00 0
#define t3_bits_01 1
#define t3_bits_10 2
#define t3_bits_11 3
#define t3_bits_000 0
#define t3_bits_001 1
#define t3_bits_010 2
#define t3_bits_011 3
#define t3_bits_100 4
#define t3_bits_101 5
#define t3_bits_110 6
#define t3_bits_111 7

typedef enum T3_Flag_Type { Set, Clear, Toggle } T3_Flag_Type;

void T3_Helper_Binary_Flag(T3_Flag_Type type, byte *value, byte flag);
bool T3_Helper_Binary_HasFlag(byte value, byte flag);
byte T3_Helper_Binary_Mask(byte value, byte mask);
char *T3_Helper_Binary_ToString(byte num);


/** -------------------------------- SDL_RECT ----------------------------------- */

SDL_Rect T3_Helper_SDL_Rect_Init(int x, int y, int w, int h);

#endif
