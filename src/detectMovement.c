#include "detectMovement.h"

// returns size 10 array of points
struct point* detectMovement(struct point frames[6][10], volatile unsigned int* in_data) {
	struct point fingers[10] = { 0 };
	int finger_number = 0;
	find_fingers(in_data, fingers, &finger_number);

    // updating the 6 most recent image frames
	for (int j = 0; j<10; j++) {
		frames[0][j] = frames[1][j];
		frames[1][j] = frames[2][j];
		frames[2][j] = frames[3][j];
		frames[3][j] = frames[4][j];
		frames[4][j] = frames[5][j];
		frames[5][j] = fingers[j];
	}

	char move[6][10];
	for (int i = 1; i<6; i++) {
		for (int j = 0; j<10; j++) {

            // count as same finger if it has not moved by more than 30 pixels in the x direction
			if (abs(frames[i][j].x - frames[i - 1][j].x) <= 30) {
                // if that finger has moved down, registed 'd' (down)
				if (frames[i][j].y - frames[i - 1][j].y>0) {
					move[i - 1][j] = 'd';
				}
                // if that finger has moved down, registed 'u' up
				if (frames[i][j].y - frames[i - 1][j].y<=0) {
					move[i - 1][j] = 'u';
				}
			}
		}
	}


    // for each finger check, if there have been 3 downs followed by 3 ups, count this as a keystroke
	struct point lowestpoint[10];
	for (int i = 0; i< 10; i++) {
		if (move[1][i] == 'd') {
			if (move[2][i] == 'd') {
				if (move[3][i] == 'u') {
					if (move[4][i] == 'u') {
						if (move[5][i] == 'u') {
							if(lowestpoint[i].y<frames[2][i].y)
							lowestpoint[i].x = frames[2][i].x;
							lowestpoint[i].y = frames[2][i].y;
						}
					}
				}
			}
		}
	}
    return lowestpoint;
}