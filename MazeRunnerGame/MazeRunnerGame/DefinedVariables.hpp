#pragma once
#include <memory>

//@DESCR: Parameters of screen

//change
#define SCREEN_HEIGHT 850 // change from 700 -> 960
#define SCREEN_WIDTH 1050 // change from 1050 -> 1280
#define SIZE_ROW 13
#define SIZE_COL 21
#define FRAME 60
#define NAME_GAME "MAZE RUNNER GAME"
#define SIZE_CELL 50
#define SPACE 10

//=========================================
// SCREEN_MAZE_WIDTH = MAZE_X * 32
// SCREEN_MAZE_HEIGHT = MAZE_Y * 32
#define SCREEN_MAZE_HEIGHT 720
#define SCREEN_MAZE_WIDTH 720

#define OFFSET_MAZE_Y (SCREEN_HEIGHT - SCREEN_MAZE_HEIGHT - SPACE)
#define OFFSET_MAZE_X SPACE

#define MAZE_Y 20
#define MAZE_X 20
//=========================================

const float OBJECT_WIDTH = 50;
const float OBJECT_HEIGHT = 50;

