#include "findFingers.h"

void findFingers (volatile unsigned int* in_data, struct point fingers[], int* finger_num) {

#pragma HLS INTERFACE s_axilite port=return

#pragma HLS INTERFACE m_axi depth=2073600 port=in_data offset=slave // This will NOT work for resolutions higher than 1080p
#pragma HLS INTERFACE m_axi depth=2073600 port=out_data offset=slave

	int y;
	int x;

	for (y = 0; y < HEIGHT; ++y) {

		int last_grey = 0;

		for (x = 0; x < WIDTH; ++x) {

			#pragma HLS PIPELINE II=1
			#pragma HLS LOOP_FLATTEN off

			unsigned int current = *in_data++;

			unsigned char in_r = current & 0xFF;
			unsigned char in_g = (current >> 8) & 0xFF;
			unsigned char in_b = (current >> 16) & 0xFF;

			
			if ((in_g-in_r > 150)&&(in_g-in_b > 150)){ // checking if current pixel is green
				
                bool stored = false;

				if (*finger_num != 0){
                    
                    //checking if fingers have been stored

					for (int i = 0; i < *finger_num; i++){
						int delta_x = fingers[i].x - x;
						int delta_y = fingers[i].y - y;

                        // if the new blue pixel is within 50 pixels of one of the previous ones it is
                        // seen as the same pixel, if it's y position is less than the previous instance
                        // the position is updated (hence favoring downwards movement)

						if ((abs(delta_x) < 50)&&(abs(delta_y) < 50)){
							if (fingers[i].y < y){
								fingers[i].x = x;
								fingers[i].y = y;
							}
							stored = true;
						}
					}
				}

                // if the finger isn't within 50 pixels of the last count it as a new finger.
				if ((stored == false)&&(finger_num < 10)){
					fingers[*finger_num].x = x;
					fingers[*finger_num].y = y;
					*finger_num = *finger_num + 1;
				}
			}
		}

	}
}
