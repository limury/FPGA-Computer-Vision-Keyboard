#include "findCorners.h"

/*
corner.c1: top left
corner.c2: top right
corner.c3: bottom left
corner.c4: bottom right
*/

struct corners findCorners (volatile unsigned int* in_data, volatile unsigned int* out_data) {
#pragma HLS INTERFACE s_axilite port=return

#pragma HLS INTERFACE m_axi depth=2073600 port=in_data offset=slave // This will NOT work for resolutions higher than 1080p
#pragma HLS INTERFACE m_axi depth=2073600 port=out_data offset=slave

    struct corners corner;

    /*
    Setting the 4 respective corners to their opposite extrema 
    in order for updates to happen as quickly as possible
    */
    corner.c1.x = WIDTH;
    corner.c1.y = HEIGHT;
    corner.c2.x = 0;
    corner.c2.y = HEIGHT;
    corner.c3.x = WIDTH;
    corner.c3.y = 0;
    corner.c4.x = 0;
    corner.c4.y = 0;

	for (int y = 0; y < HEIGHT; y++) {

		int last_grey = 0;

		for (int x = 0; x < WIDTH; ++x) {

			#pragma HLS PIPELINE II=1
			#pragma HLS LOOP_FLATTEN off

			unsigned int current = *in_data++;

			unsigned char in_r = current & 0xFF;
			unsigned char in_g = (current >> 8) & 0xFF;
			unsigned char in_b = (current >> 16) & 0xFF;

			if ((in_r - in_b > 150) || (in_r - in_g > 150)){ // detects red
				
                // if distance from top left corner is less for the newfound red, update the value of corner1
                if ((corner.c1.x + corner.c2.y) > (x + y)){
                    corner.c1.x = x;
                    corner.c1.y = y;
                }

                // if distance from top right corner is less for the newfound red, update the value of corner2
                if (( corner.c2.y - corner.c2.x) > (y - x)){
                    corner.c2.x = x;
                    corner.c2.y = y;
                }

                // if distance from bottom left corner is less for the newfound red, update the value of corner3
                if (( corner.c3.x - corner.c3.y) > (x - y)){
                    corner.c3.x = x;
                    corner.c3.y = y;
                }

                // if distance from bottom right corner is less for the newfound red, update the value of corner4
                if (( corner.c4.x + corner.c4.y) < (x + y)){
                    corner.c4.x = x;
                    corner.c4.y = y;
                }
                
			}

		}

	}
    return corner;
}