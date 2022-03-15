#ifndef SOBELDETECTION
#define SOBELDETECTION

#include "includes.h"
#include "routines.h"

/*
Function: sobelDetection
------------------------
Sobel edge detection works by convoluting 3x3 areas of the image (greyscale) 
with 2 gradient detection matrices, one used to check for vertical edges, one for horizontal edges.
Once the values for the convolution are calculated they can be used to find the angle of the edge and
hence decide if it is a vertical or horizontal line

Inputs: 
horizontal_lines[WIDTH][15]: This is an array of a given width, which stores, for every x coordinate of 
                             the image, the y coordinates of every line present at that specific x value.
vertical_lines[HEIGHT][6]:   This is an array of a given height, which stores, for every y coordinate of 
                             the image, the x coordinates of every line present at that specific y value.
corner: A data struture containing the coordinates of the 4 corners of the keyboard, used to see if the line
        that has been found is within the limits of the keyboard or just an outside source to be ignored.
*indata: pointer to the input image

Outputs:
updated versions of horizontal_lines[WIDTH][15] and vertical_lines[HEIGHT][6]

*/

void sobelDetection(int horizontal_lines[WIDTH][15], int vertical_lines[HEIGHT][6], struct corners corner,
            volatile unsigned int* in_data);

#endif // SOBEL DETECTION