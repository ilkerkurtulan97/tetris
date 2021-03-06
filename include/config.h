#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "vec.h"
#include "mat.h"

// #define DEBUG

// define the number & size of the grid:
const int NUM_ROWS = 20;
const int NUM_COLS = 10;
const int GRID_SIZE = 40;
const float AUTO_DROP_TIME = 700; // in milliseconds
const vec3 background_color = vec3(0, 0, 0);
const vec3 grid_color = vec3(1, 1, 1);
const char GAMEOVER_FILEPATH[] = "src/gameover.bmp";

#endif