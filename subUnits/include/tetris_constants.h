/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef TETRIS_CONSTANTS
#define TETRIS_CONSTANTS

#define SHAPE_COUNT 7

#include <SDL_pixels.h>
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

extern const SDL_Color GRID_BACKGROUND_COLOR;
extern const SDL_Color GRID_LINES_COLOR;
extern const SDL_Color CLEAR_COLOR;
extern const SDL_Color SOLID_BLOCK_COLOR;
extern const SDL_Color TETROMINO_COLORS[];

extern const int shapeWidthArr[SHAPE_COUNT];

#endif