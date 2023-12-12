/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include "field_functions.h"

void initializeField(int *field) {
    for (int i = 0; i < TOTAL_NUM_OF_CELLS; ++i) {
        field[i] = 0;
    }
}

int getPosition(int row, int column, int width) {
    return row * width + column;
}

void addNewShapeToField(int *field, enum TetrisShapes shape) {
    switch (shape) {
        case STRAIGHT_TETROMINO: {
            int startPos = rand() % (FIELD_WIDTH - STRAIGHT_TETROMINO_WIDTH - 1);
            for (int i = 0; i < 4; ++i) {
                field[startPos + i] = NEW_SHAPE_PART;
            }

            return;
        }
        case SQUARE_TETROMINO: {
            int startPos = rand() % (FIELD_WIDTH - SQUARE_TETROMINO_WIDTH - 1);
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case T_TETROMINO: {
            int startPos = rand() % (FIELD_WIDTH - T_TETROMINO_WIDTH - 1);
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[startPos + 2] = NEW_SHAPE_PART;
            field[getPosition(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case L_TETROMINO: {
            int startPos = rand() % (FIELD_WIDTH - L_TETROMINO_WIDTH - 1);
            field[startPos] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(2, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case SKEW_TETROMINO: {
            int randomNum = rand() % (FIELD_WIDTH - SKEW_TETROMINO_WIDTH - 1);
            int startPos = getPosition(1, randomNum, FIELD_WIDTH);
            int firstRow = getPosition(0, randomNum + 1, FIELD_WIDTH);
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[firstRow] = NEW_SHAPE_PART;
            field[firstRow + 1] = NEW_SHAPE_PART;

            return;
        }
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void moveLeft(int *field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        if (field[getPosition(i, 0, FIELD_WIDTH)] == NEW_SHAPE_PART) {
            return;
        }
    }

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART) {
                swap(&field[currentPosition], &field[currentPosition - 1]);
            }
        }
    }
}

void moveRight(int *field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        if (field[getPosition(i, FIELD_WIDTH - 1, FIELD_WIDTH)] == NEW_SHAPE_PART) {
            return;
        }
    }

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = FIELD_WIDTH - 1; j >= 0; --j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART) {
                swap(&field[currentPosition], &field[currentPosition + 1]);
            }
        }
    }
}

bool checkCollisions(int *field) {
    bool allSolid = false;
    bool RowAlreadyCheckedAgain = false;

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currPosition] != NEW_SHAPE_PART) continue;

            if (i == FIELD_HEIGHT - 1 || allSolid || field[getPosition(i + 1, j, FIELD_WIDTH)] == SOLID) {
                allSolid = true;
                field[currPosition] = SOLID;
                if (RowAlreadyCheckedAgain == false) {
                    RowAlreadyCheckedAgain = true;
                    j = -1;
                    i = FIELD_HEIGHT;
                }
            }
        }
    }

    return allSolid;
}

bool moveDown(int *field, bool *solid) {
    if (checkCollisions(field)) {
        *solid = true;
        return false;
    };

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART) {
                swap(&field[currentPosition], &field[getPosition(i + 1, j, FIELD_WIDTH)]);
            }
        }
    }

    return true;
}

void moveNewShape(int *field, enum Directions direction, bool *solid) {
    switch (direction) {
        case LEFT: {
            moveLeft(field);
            break;
        }
        case RIGHT: {
            moveRight(field);
            break;
        }
        case DOWN: {
            moveDown(field, solid);
            break;
        }
    }
}

void dropNewShape(int *field, bool *solid) {
    while (moveDown(field, solid));
}

void rotateShape(int *field) {

}
