#include "routines.h"

void getFirstRows(volatile uint32_t* in_data, float v0[WIDTH], float v1[WIDTH], float v2[WIDTH]){

    for (int x = 0; x < WIDTH; x++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_FLATTEN off
		    unsigned int current = *in_data++;
    		v0[x] = getGreyscale(current);
    	}

	for (int x = 0; x < WIDTH; x++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_FLATTEN off
		unsigned int current = *in_data++;

		v1[x] = getGreyscale(current);
	}

	for (int x = 0; x < WIDTH; x++) {
#pragma HLS PIPELINE II=1
#pragma HLS LOOP_FLATTEN off
		unsigned int current = *in_data++;

		v2[x] = getGreyscale(current);
	}
}



inline float getGreyscale(const unsigned int current){
        return 0.2126f*(current & 0xFF) + 0.7152f*((current >> 8) & 0xFF) + 0.0722f*((current >> 16) & 0xFF);
}


int findEdge(int y, int y1, int y2, int x1, int x2) {
	double a = y1 - y2;
	double b = x1 - x2;
	double c = y - y1; 
    return (b * c) / a + x1;
}

 
void addToVector(int v[], int val, int size) {
	for (int i = 0; i < size; i++) {
		if (abs(abs(v[i]) - abs(val)) < 20) {
			v[i] = val;
			return;
		}
		else if (v[i] == 0) {
			v[i] = val;
			return;
		}
	}
}


char*** init() {

    char* keyboard[5][14];
	keyboard[0][0]= "`";
	keyboard[0][1]= "1";
	keyboard[0][2]= "2";
	keyboard[0][3]= "3";
	keyboard[0][4]= "4";
	keyboard[0][5]= "5";
	keyboard[0][6]= "6";
	keyboard[0][7]= "7";
	keyboard[0][8]= "8";
	keyboard[0][9]= "9";
	keyboard[0][10]= "0";
	keyboard[0][11]= "-";
	keyboard[0][12]= "=";
	keyboard[0][13]= "BS";
	keyboard[1][0]= "    ";
	keyboard[1][1]= "q";
	keyboard[1][2]= "w";
	keyboard[1][3]= "e";
	keyboard[1][4]= "r";
	keyboard[1][5]= "t";
	keyboard[1][6]= "y";
	keyboard[1][7]= "u";
	keyboard[1][8]= "i";
	keyboard[1][9]= "o";
	keyboard[1][10]= "p";
	keyboard[1][11]= "[";
	keyboard[1][12]= "]";
	keyboard[1][13]= "\n";
	keyboard[2][0]= "CL";
	keyboard[2][1]= "a";
	keyboard[2][2]= "s";
	keyboard[2][3]= "d";
	keyboard[2][4]= "f";
	keyboard[2][5]= "g";
	keyboard[2][6]= "h";
	keyboard[2][7]= "j";
	keyboard[2][8]= "k";
	keyboard[2][9]= "l";
	keyboard[2][10]= ";";
	keyboard[2][11]= "'";
	keyboard[2][12]= "#";
	keyboard[2][13]= "\n";
	keyboard[3][0]= "CL";
	keyboard[3][1]= "\\";
	keyboard[3][2]= "z";
	keyboard[3][3]= "x";
	keyboard[3][4]= "c";
	keyboard[3][5]= "v";
	keyboard[3][6]= "b";
	keyboard[3][7]= "n";
	keyboard[3][8]= "m";
	keyboard[3][9]= ",";
	keyboard[3][10]= ".";
	keyboard[3][11]= "/";
	keyboard[3][12]= "CL";
	keyboard[3][13]= "CL";
	keyboard[4][0]= "Ctrl";
	keyboard[4][1]= "Fn";
	keyboard[4][2]= "Wndw";
	keyboard[4][3]= "Alt";
	keyboard[4][4]= " ";
	keyboard[4][5]= " ";
	keyboard[4][6]= " ";
	keyboard[4][7]= " ";
	keyboard[4][8]= " ";
	keyboard[4][9]= "Alt Gr";
	keyboard[4][10]= "CTRL";
	keyboard[4][11]= "Left";
	keyboard[4][12]= "UP";
	keyboard[4][13]= "Right";
    return keyboard;
}
