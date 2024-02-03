#include "core/helpers.h"

bool T3_Helper_Random_Bool() {
    return rand() % 2 == 0;
}

int T3_Helper_Random_Sign() {
    return (rand() % 2 == 0) ? 1 : -1;
}

int T3_Helper_Random_Int(int min, int max) {
    T3_HELPER_ASSERT(min <= max, "Min value cannot be lower than Max!");
    return min + rand() % (max - min + 1);
}

float T3_Helper_Random_Float(float min, float max) {
    T3_HELPER_ASSERT(min <= max, "Min value cannot be lower than Max.");

    //Generate a random float between 0 and 1 with specified precision
    float random_float_0_to_1 = ((float) rand() / (float) RAND_MAX);
    //TODO: Revisit this method later.
    return min + random_float_0_to_1 * (max - min);
}