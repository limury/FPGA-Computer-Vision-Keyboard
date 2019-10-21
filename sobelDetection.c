
#include "sobelDetection.h"

void sobelDetection(int horizontal_lines[WIDTH][15], int vertical_lines[HEIGHT][6], struct corners corner,
            volatile unsigned int* in_data) {

    /* Creating array of WIDTH equal to the max screen size,
    stores the greyscale values of 3 rows of pixels in order to apply the 3x3 matrix convolution filter
    */

	float v0[WIDTH] = { 0 };
	float v1[WIDTH] = { 0 };
	float v2[WIDTH] = { 0 };
	
    /*
    Retrieve first 3 rows of grayscale values for the image
    */
    getFirstRows(in_data, v0, v1, v2);


	for (int y = 3; y < HEIGHT; y++) {
        
		float v_new[WIDTH] = { 0 }; // Initialising temporary array that will substitute v3
		
        /*
        as the edge detection filter is a 3x3 matrix, the first and the last pixel value 
        of each column are not referred to as a possible edge, hence their value is simply 
        placed into v_new[0] and v_new[w-1]
        */
        unsigned int current = *in_data++;
		v_new[0] = getGreyscale(current);



		for (int x = 1; x < WIDTH - 1; x++) {
    #pragma HLS PIPELINE II=1
    #pragma HLS LOOP_FLATTEN off
			
            current = *in_data++;
			float curr_grey = getGreyscale(current);

			v_new[x] = curr_grey;

            /*
            Checks if current coordinates are within the borders of the keyboard,
            if they are not, any edges won't be detected
            */
			if (x >= findEdge(y - 2, corner.c1.y, corner.c3.y, corner.c1.x, corner.c3.x) && //checking x is within left border
                x<= findEdge(y - 2, corner.c4.y, corner.c2.y, corner.c4.x, corner.c2.x) && //checking x is within right border
                y - 2 <= fmin(corner.c3.y, corner.c4.y) &&  // checking y is within bottom border
                y - 2 >= fmax(corner.c1.y, corner.c2.y)) { // checking y is within top border
				float convolutionx, convolutiony;

                /* convolution in both x and y direction
                Horizontal detection filter:
                {
		        { -1, 0, 1 },
        	    { -2, 0, 2 },
        	    { -1, 0, 1 }
        	    }
        	    Vertical detection filter:
                {
        		{ -1, -2, -1 },
        	    { 0, 0, 0 },
        	    { 1, 2, 1 }
        	    }
                */
				convolutionx = 
					v0[x + 1] +
					v1[x + 1] * 2 +
					v2[x + 1] -
                    v0[x - 1] -
					v1[x - 1] * 2 -
					v2[x - 1];

				convolutiony = 
					v2[x - 1] +
					v2[x] * 2 +
					v2[x + 1] -
                    v0[x - 1] -
					v0[x] * 2 -
					v0[x + 1];


				float pheta = atan(convolutiony / convolutionx);
				if (abs(convolutionx) + abs(convolutiony) > 200) { // if the two convolutions add up to a value over 200 that is considered an edge
					if (abs(pheta) > pi / 3) { // if pheta is more than pi/3 count the line as horizontal
						addToVector(horizontal_lines[x], y - 2, 6);

					}
					else {
						addToVector(vertical_lines[y - 2], x, 15); // if pheta is less than pi/3 count it as vertical
					}
				}
			}
		}

		current = *in_data++;
		v_new[WIDTH - 1] = getGreyscale(current);

        // replacing the old v0[], v1[], v2[] 
		for (int i = 0; i < WIDTH; i++) {
			v0[i] = v1[i];
			v1[i] = v2[i];
			v2[i] = v_new[i];
		}

	}
}