#ifndef T3_RANDOMISATION_H
#define T3_RANDOMISATION_H

/**
 * Generate a boolean random (returns true or false)
 */
bool T3_Random_Bool();

/**
 * Generate a random sign (returns +1 or -1)
 */
int T3_Random_Sign();

/**
 * Generate a random int from a range [min to max]
 */
int T3_Random_Int(int min, int max);

/**
 * Generate a random float from a range [min to max]
 */
float T3_Random_Float(float min, float max);

#endif //T3_RANDOMISATION_H