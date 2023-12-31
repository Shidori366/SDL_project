/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef TETRIS_TYPES
#define TETRIS_TYPES

enum TetrisFieldCellStates {
    EMPTY = 0,
    SOLID = 1,
    NEW_SHAPE_PART = 2,
    NEW_SHAPE_PIVOT = 3,
};

// TODO: Change shapes according to task assignment
enum TetrisShapes {
    STRAIGHT_TETROMINO,
    SQUARE_TETROMINO,
    T_TETROMINO,
    L_TETROMINO,
    REVERSE_L_TETROMINO,
    SKEW_TETROMINO,
    REVERSE_SKEW_TETROMINO
};

enum Directions {
    RIGHT,
    DOWN,
    LEFT
};

enum Scenes {
    MENU,
    GAME,
    GAME_OVER,
};

typedef struct Position {
    int x;
    int y;
} Position;

#endif //TETRIS_TYPES
