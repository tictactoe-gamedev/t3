#ifndef T3_RANDOMISATION_H
#define T3_RANDOMISATION_H

void T3_Init_Random();                                      //Initialize the random generator seed (time)

bool T3_Random_Bool();                                      //Generate a boolean random (returns true or false)

int T3_Random_Sign();                                       //Generate a random sign (returns +1 or -1)

int T3_Random_Int(int min, int max);                        //Generate a random int from a range [min to max]

float T3_Random_Float(float min, float max);                //Generate a random float from a range [min to max]

#endif //T3_RANDOMISATION_H