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
    int startPos = rand() % (FIELD_WIDTH - shapeWidthArr[shape] + 1);

    switch (shape) {
        case STRAIGHT_TETROMINO: {
            for (int i = 0; i < 4; ++i) {
                field[getPosition(i, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            }
            field[getPosition(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PIVOT;

            return;
        }
        case SQUARE_TETROMINO: {
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case T_TETROMINO: {
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PIVOT;
            field[startPos + 2] = NEW_SHAPE_PART;
            field[getPosition(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case L_TETROMINO: {
            field[startPos] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PIVOT;
            field[getPosition(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(2, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case REVERSE_L_TETROMINO: {
            ++startPos;
            field[startPos] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PIVOT;
            field[getPosition(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(2, startPos - 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case SKEW_TETROMINO: {
            ++startPos;
            int secondRow = getPosition(1, startPos, FIELD_WIDTH);

            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[secondRow] = NEW_SHAPE_PIVOT;
            field[secondRow - 1] = NEW_SHAPE_PART;

            return;
        }
        case REVERSE_SKEW_TETROMINO: {
            int secondRow = getPosition(1, startPos + 1, FIELD_WIDTH);

            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[secondRow] = NEW_SHAPE_PIVOT;
            field[secondRow + 1] = NEW_SHAPE_PART;

            return;
        }
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

bool checkBlockSideCollisions(const int *field, enum Directions direction) {
    int moveBy = direction == RIGHT ? 1 : -1;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if ((field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) &&
                field[currentPosition + moveBy] == SOLID) {
                return true;
            }
        }
    }

    return false;
}

void moveLeft(int *field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        int currentPosition = getPosition(i, 0, FIELD_WIDTH);
        if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
            return;
        }
    }

    if (checkBlockSideCollisions(field, LEFT) == true) return;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
                swap(&field[currentPosition], &field[currentPosition - 1]);
            }
        }
    }
}

void moveRight(int *field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        int currentPosition = getPosition(i, FIELD_WIDTH - 1, FIELD_WIDTH);
        if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
            return;
        }
    }

    if (checkBlockSideCollisions(field, RIGHT) == true) return;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = FIELD_WIDTH - 1; j >= 0; --j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
                swap(&field[currentPosition], &field[currentPosition + 1]);
            }
        }
    }
}

bool checkGroundCollisions(int *field) {
    bool allSolid = false;
    bool checkAllAgain = true;
    int numOfSolid = 0;

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currPosition] != NEW_SHAPE_PART && field[currPosition] != NEW_SHAPE_PIVOT) {
                continue;
            }

            if (i == FIELD_HEIGHT - 1 || allSolid || field[getPosition(i + 1, j, FIELD_WIDTH)] == SOLID) {
                allSolid = true;
                field[currPosition] = SOLID;
                if (++numOfSolid == 4) {
                    return true;
                }

                if (checkAllAgain) {
                    checkAllAgain = false;
                    j = -1;
                    i = FIELD_HEIGHT;
                }
            }
        }
    }

    return false;
}

void removeFilledRow(int *field, const int rowToRemoveIndex) {
    for (int i = rowToRemoveIndex - 1; i >= 0; --i) {
        int currentPosition = getPosition(i + 1, 0, FIELD_WIDTH);
        int rowAboveCurrentPosition = getPosition(i, 0, FIELD_WIDTH);

        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (field[rowAboveCurrentPosition] == SOLID) {
                field[currentPosition] = SOLID;
            } else {
                field[currentPosition] = EMPTY;
            }

            ++currentPosition;
            ++rowAboveCurrentPosition;
        }
    }

}

void checkAndRemoveFilledRows(int *field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] != SOLID) {
                break;
            }
            if (j == FIELD_WIDTH - 1) {
                removeFilledRow(field, i);
            }
        }
    }
}

bool moveDown(int *field, bool *solid) {
    if (checkGroundCollisions(field)) {
        *solid = true;
        checkAndRemoveFilledRows(field);
        return false;
    };

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
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
    Position partPositions[3];
    Position pivotPosition;
    FILE *f = fopen("positions.txt", "w");

    int partIndex = 0;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = getPosition(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART) {
                partPositions[partIndex] = (Position) {j, i};
                ++partIndex;
            }
            if (field[currentPosition] == NEW_SHAPE_PIVOT) {
                pivotPosition = (Position) {j, i};
            }
        }
    }

    // TODO: calculate next positions (pivot is origin, 90 degrees)

    fclose(f);
}
