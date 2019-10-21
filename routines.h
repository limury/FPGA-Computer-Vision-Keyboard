/*
This file defines some routines used across the program 
which would be too verbose to repeat when needed
*/

#ifndef UNCOMMON_ROUTINES
#define UNCOMMON_ROUTINES

#include "includes.h"

/*
Function: getFirstRows
----------------------
Gets the first 3 rows of pixels of the image

Inputs:
    in_data*: data from the image
    v0, v1, v2: arrays of floats corresponding to the greyscale value of the rows

Outputs:
    v0, v1, v2: passed by reference and modified

*/
void getFirstRows(volatile uint32_t* in_data, float v0[WIDTH], float v1[WIDTH], float v2[WIDTH]);

/*
Function: getGrayscale
----------------------
Returns greyscale value of the rgb input "current"

Inputs:
    current: a hex RGB value of a pixel

Output:
    grayscale version of current
*/
inline float getGreyscale(const unsigned int current);

/*
Function: findEdge
------------------
Given 2 points, and a y coordinate, this function finds the equation of the line between the two points 
and returns the x value of the line at the given y coordinate

Inputs:
    x1, y1, x2, y2: x and y coordinates of the 2 points respectively
    y: y coordinate for which the relevant x value should be calculated

Outputs:
    x value of the line at y coordinate "y"

IMPORTANT:
    x2, y2 must ALWAYS point to the rightmost point
*/
int findEdge(int y, int y1, int y2, int x1, int x2);


/*
Function: addToVector
---------------------
Adds the coordinate of the currently found line, if this coordinate happens to be 20 pixels 
or less away from another in the same array these are registered as the same edge

Inputs:
    v[]: array storing coordinates of each instance of an edge in a given direction (more on this in readme file)
    val: coordinate of the currently found edge
    size: size of the array v[]

Output:
    updated version of v[]
*/
void addToVector(int v[], int val, int size);

/*
Function: init
--------------
Outputs the keyboard layout (customizable)

*/
char*** init();   



#endif