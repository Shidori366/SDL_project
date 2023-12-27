/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef TETRIS_CONSTANTS
#define TETRIS_CONSTANTS

#define SHAPE_COUNT 7

#include <SDL2/SDL_pixels.h>
#include "tetris_types.h"

extern const int SIDEBAR_WIDTH;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const int FIELD_WIDTH;
extern const int FIELD_HEIGHT;
extern const int STARTING_POSITION_HEIGHT;
extern const int TOTAL_NUM_OF_CELLS;

extern const int GRID_WIDTH_PX;

extern const int BLOCK_WIDTH;
extern const int BLOCK_HEIGHT;

extern const int SCORE_TEXT_FONT_PT_SIZE;
extern const int SCORE_VALUE_FONT_PT_SIZE;
extern const SDL_Color SCORE_FONT_COLOR;
extern const char *ROBOTO_REGULAR_FONT_PATH;

extern const SDL_Color GRID_BACKGROUND_COLOR;
extern const SDL_Color GRID_LINES_COLOR;
extern const SDL_Color CLEAR_COLOR;
extern const SDL_Color SOLID_BLOCK_COLOR;
extern const SDL_Color TETROMINO_COLORS[];

extern const int shapeWidthArr[SHAPE_COUNT];

#endif