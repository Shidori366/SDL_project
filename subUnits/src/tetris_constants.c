/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include "tetris_constants.h"

const int STARTING_POSITION_HEIGHT = 4;
const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 20 + STARTING_POSITION_HEIGHT;
const int TOTAL_NUM_OF_CELLS = FIELD_WIDTH * FIELD_HEIGHT + FIELD_WIDTH * STARTING_POSITION_HEIGHT;

const int SIDEBAR_WIDTH = 200;

const int WINDOW_WIDTH = 300 + SIDEBAR_WIDTH;
const int WINDOW_HEIGHT = 720;

const int GRID_WIDTH_PX = WINDOW_WIDTH - SIDEBAR_WIDTH;

const int BLOCK_WIDTH = GRID_WIDTH_PX / FIELD_WIDTH;
const int BLOCK_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

const int STRAIGHT_TETROMINO_WIDTH = 4;
const int SQUARE_TETROMINO_WIDTH = 2;
const int T_TETROMINO_WIDTH = 3;
const int L_TETROMINO_WIDTH = 2;
const int SKEW_TETROMINO_WIDTH = 3;

const int SHAPE_COUNT = 5;

const SDL_Color GRID_BACKGROUND_COLOR = {
        25,
        25,
        25,
        255
};

const SDL_Color GRID_LINES_COLOR = {
        0,
        0,
        0,
        255
};

const SDL_Color CLEAR_COLOR = {
        0,
        0,
        0,
        255
};

const SDL_Color SOLID_BLOCK_COLOR = {
        200,
        200,
        200,
        255
};