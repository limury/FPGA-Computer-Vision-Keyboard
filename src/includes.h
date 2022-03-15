#ifndef INCLUDES
#define INCLUDES

#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define pi 3.14159265
#define WIDTH 1920
#define HEIGHT 1080

struct key {
	char primary_char;
};

struct point {
	int x;
	int y;
};

struct corners {
    struct point c1;
    struct point c2;
    struct point c3;
    struct point c4;
};

#endif //INCLUDES