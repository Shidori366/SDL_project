/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef TETRIS_CONSTANTS
#define TETRIS_CONSTANTS

#include <SDL_pixels.h>

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

extern const int STRAIGHT_TETROMINO_WIDTH;
extern const int SQUARE_TETROMINO_WIDTH;
extern const int T_TETROMINO_WIDTH;
extern const int L_TETROMINO_WIDTH;
extern const int SKEW_TETROMINO_WIDTH;

extern const int SHAPE_COUNT;

enum TetrisFieldCellStates {
    EMPTY = 0,
    SOLID = 1,
    NEW_SHAPE_PART = 2,
};

// TODO: Change shapes according to task assignment
enum TetrisShapes {
    STRAIGHT_TETROMINO,
    SQUARE_TETROMINO,
    T_TETROMINO,
    L_TETROMINO,
    SKEW_TETROMINO
};

enum Directions {
    RIGHT,
    DOWN,
    LEFT
};

#endif