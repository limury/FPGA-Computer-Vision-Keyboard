#ifndef FINDCORNERS
#define FINDCORNERS

#include "includes.h"
#include "routines.h"

/*
Function: findCorners
---------------------
This function finds the 4 corners of the drawn out keyboard, 
these must be bright red and quite large to be detected (depending on camera quality),
red is detected using the following boundaries: (rgb_red - rgb_blue > 150) OR (rgb_red - rgb_green > 150)

Inputs:
    in_data: pointer to input pixel data from the image
    out_data: pointer to output data for the image

Output:
    struct corner: a struct containing 4 points, each representing a different corner of the keyboard
*/

struct corners findCorners (volatile unsigned int* in_data, volatile unsigned int* out_data);

#endif