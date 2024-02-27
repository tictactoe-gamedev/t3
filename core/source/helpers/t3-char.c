#include "t3-helpers.h"

void T3_Char_Assign_Unsafe (char *string, const char *value, uint32 start_index, uint32 end_index) {
    uint32 currValueIndex;
    uint32 currStringIndex;
    currStringIndex = 0;

    for (currValueIndex = start_index; currValueIndex <= end_index; ++currValueIndex) {
        string[currStringIndex] = value[currValueIndex];
        if (value[currValueIndex] == '\0') {
            return;
        }
        ++currStringIndex;
    }
}
