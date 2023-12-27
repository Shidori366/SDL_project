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

const int SCORE_TEXT_FONT_PT_SIZE = 25;
const int SCORE_VALUE_FONT_PT_SIZE = 15;
const SDL_Color SCORE_FONT_COLOR = {
        255,
        255,
        255,
        0
};

const char *ROBOTO_REGULAR_FONT_PATH = "../resources/fonts/Roboto-Regular.ttf";

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

const int shapeWidthArr[SHAPE_COUNT] = {
        1, 2, 3, 2, 2, 3, 3
};

const SDL_Color TETROMINO_COLORS[] = {
        {202, 5,   5,   255},
        {130, 202, 5,   255},
        {5,   202, 193, 255},
        {5,   202, 17,  255},
        {219, 231, 33,  255},
        {118, 5,   202, 255},
        {202, 5,   85,  255}
};