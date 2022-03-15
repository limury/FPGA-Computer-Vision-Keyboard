#ifndef FINDFINGERS
#define FINDFINGERS
#include "includes.h"


/*
Function: findFingers
---------------------
Detects the position of fingers on the image (denoted by a green spot placed on each finger)

Inputs:
    *in_data: pointer to the image data in memory
    fingers[]: array to be filled with the new position of each finger
    *finger_num = variable to be passed each time this function is called 
                  to keep track of how many fingers are on screen

Output:
    updated version of the array fingers[] with the new finger locations
*/
void findFingers (volatile unsigned int* in_data, struct point fingers[], int* finger_num);


#endif
