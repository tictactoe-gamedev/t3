#include <SDL_assert.h>
#include "t3-helpers.h"

bool T3_Helper_Random_Bool(void) {
    return rand() % 2 == 0;
}

int T3_Helper_Random_Sign(void) {
    return (rand() % 2 == 0) ? 1 : -1;
}

int T3_Helper_Random_Int(int min, int max) {
    SDL_assert(min<=max);
    return min + rand() % (max - min + 1);
}

float T3_Helper_Random_Float(float min, float max) {
    float random_float_0_to_1;
    SDL_assert(min <= max);
    
    /*Generate a random float between 0 and 1 with specified precision*/
    random_float_0_to_1 = ((float) rand() / (float) RAND_MAX);
    /*TODO: Revisit this method later.*/
    return min + random_float_0_to_1 * (max - min);
}
