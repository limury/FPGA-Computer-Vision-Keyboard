#ifndef DETECTMOVEMENT
#define DETECTMOVEMENT

#include "includes.h"

/*
Function: detectMovement
------------------------
Detects movement of the fingers and returns an array of the points 
at which a keystroke has been detected (max 10)

Inputs:
    frames[6][10]: this array stores 6 instances of the position of the 10 fingers
    *in_data: pointer to input image data

Output: 
    array of points (max 10) which represent the points at which keystrokes have been detected
*/
struct point* detectMovement(struct point frames[6][10], volatile unsigned int* in_data);

#endif //DETECTMOVEMENT