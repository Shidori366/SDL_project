/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <field_functions.h>

void initializeField(int *field) {
    for (int i = 0; i < TOTAL_NUM_OF_CELLS; ++i) {
        field[i] = 0;
    }
}

int get1dIndex(int row, int column, int width) {
    return row * width + column;
}

void addNewShapeToField(int *field, enum TetrisShapes shape) {
    int startPos = rand() % (FIELD_WIDTH - shapeWidthArr[shape] + 1);

    switch (shape) {
        case STRAIGHT_TETROMINO: {
            for (int i = 0; i < 4; ++i) {
                field[get1dIndex(i, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            }
            field[get1dIndex(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PIVOT;

            return;
        }
        case SQUARE_TETROMINO: {
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[get1dIndex(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[get1dIndex(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case T_TETROMINO: {
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PIVOT;
            field[startPos + 2] = NEW_SHAPE_PART;
            field[get1dIndex(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case L_TETROMINO: {
            field[startPos] = NEW_SHAPE_PART;
            field[get1dIndex(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PIVOT;
            field[get1dIndex(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[get1dIndex(2, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case REVERSE_L_TETROMINO: {
            ++startPos;
            field[startPos] = NEW_SHAPE_PART;
            field[get1dIndex(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PIVOT;
            field[get1dIndex(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[get1dIndex(2, startPos - 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case SKEW_TETROMINO: {
            ++startPos;
            int secondRow = get1dIndex(1, startPos, FIELD_WIDTH);

            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[secondRow] = NEW_SHAPE_PIVOT;
            field[secondRow - 1] = NEW_SHAPE_PART;

            return;
        }
        case REVERSE_SKEW_TETROMINO: {
            int secondRow = get1dIndex(1, startPos + 1, FIELD_WIDTH);

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
            int currentPosition = get1dIndex(i, j, FIELD_WIDTH);
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
        int currentPosition = get1dIndex(i, 0, FIELD_WIDTH);
        if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
            return;
        }
    }

    if (checkBlockSideCollisions(field, LEFT) == true) return;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = get1dIndex(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
                swap(&field[currentPosition], &field[currentPosition - 1]);
            }
        }
    }
}

void moveRight(int *field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        int currentPosition = get1dIndex(i, FIELD_WIDTH - 1, FIELD_WIDTH);
        if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
            return;
        }
    }

    if (checkBlockSideCollisions(field, RIGHT) == true) return;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = FIELD_WIDTH - 1; j >= 0; --j) {
            int currentPosition = get1dIndex(i, j, FIELD_WIDTH);
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
            int currPosition = get1dIndex(i, j, FIELD_WIDTH);
            if (field[currPosition] != NEW_SHAPE_PART && field[currPosition] != NEW_SHAPE_PIVOT) {
                continue;
            }

            if (i == FIELD_HEIGHT - 1 || allSolid || field[get1dIndex(i + 1, j, FIELD_WIDTH)] == SOLID) {
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
        int currentPosition = get1dIndex(i + 1, 0, FIELD_WIDTH);
        int rowAboveCurrentPosition = get1dIndex(i, 0, FIELD_WIDTH);

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

int checkAndRemoveFilledRows(int *field) {
    int rowsRemoved = 0;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = get1dIndex(i, j, FIELD_WIDTH);
            if (field[currentPosition] != SOLID) {
                break;
            }
            if (j == FIELD_WIDTH - 1) {
                removeFilledRow(field, i);
                ++rowsRemoved;
            }
        }
    }

    return rowsRemoved;
}

void addToScore(unsigned int *score, int rowsRemoved) {
    if (rowsRemoved == 1) {
        *score += 100;
    } else if (rowsRemoved == 2) {
        *score += 300;
    } else if (rowsRemoved == 3) {
        *score += 500;
    } else if (rowsRemoved > 3) {
        *score += (rowsRemoved / 3) * 500;
        *score += (rowsRemoved % 3) == 2 ? 300 : 100;
    }
}

bool moveDown(int *field, bool *solid, unsigned int *score) {
    if (checkGroundCollisions(field)) {
        *solid = true;
        int rowsRemoved = checkAndRemoveFilledRows(field);
        addToScore(score, rowsRemoved);
        return false;
    }

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = get1dIndex(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART || field[currentPosition] == NEW_SHAPE_PIVOT) {
                swap(&field[currentPosition], &field[get1dIndex(i + 1, j, FIELD_WIDTH)]);
            }
        }
    }

    return true;
}

void moveNewShape(int *field, enum Directions direction, bool *solid, unsigned int *score) {
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
            moveDown(field, solid, score);
            break;
        }
    }
}

void dropNewShape(int *field, bool *solid, unsigned int *score) {
    while (moveDown(field, solid, score));
}

Position rotatePoint(Position origin, Position point, int *xOutOfBounds, int *yOutOfBounds) {
    Position rotatedPoint = {0, 0};

    double x = point.x - origin.x;
    double y = point.y - origin.y;
    double radian = (90 * M_PI) / 180;
    double newX = (x * cos(radian) - y * sin(radian)) + origin.x;
    double newY = (x * sin(radian) + y * cos(radian)) + origin.y;
    rotatedPoint.x = (int) round(newX);
    rotatedPoint.y = (int) round(newY);

    if (newX < 0) {
        *xOutOfBounds = 1;
    } else if (newX >= FIELD_WIDTH) {
        *xOutOfBounds = 2;
    }
    if (newY < 0) {
        *yOutOfBounds = 1;
    } else if (newY >= FIELD_HEIGHT) {
        *xOutOfBounds = 2;
    }

    return rotatedPoint;
}

int calculateOffset(int outOfBounds, Position *points, bool x) {
    int offset = 0;
    if (outOfBounds == 1) {
        for (int i = 0; i < 4; ++i) {
            int pointCoord = x ? points[i].x : points[i].y;
            if (offset > pointCoord) {
                offset = pointCoord;
            }
        }

        offset *= -1;
    } else {
        for (int i = 0; i < 4; ++i) {
            int pointCoord = x ? points[i].x : points[i].y;
            if (offset < pointCoord) {
                offset = pointCoord;
            }
        }

        offset = FIELD_WIDTH - offset - 1;
    }

    return offset;
}

void offsetPoints(int xOutOfBounds, int yOutOfBounds, Position *points) {
    if (xOutOfBounds) {
        int xOffset = calculateOffset(xOutOfBounds, points, true);
        for (int i = 0; i < 4; ++i) {
            points[i].x += xOffset;
        }
    }
    if (yOutOfBounds) {
        int yOffset = calculateOffset(yOutOfBounds, points, false);
        for (int i = 0; i < 4; ++i) {
            points[i].y += yOffset;
        }
    }
}

void rotateShape(int *field) {
    Position partPositions[3];
    Position newPartPositions[4];
    Position pivotPosition = {-1, -1};

    int partIndex = 0;

    // Getting all new shape positions
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            int currentPosition = get1dIndex(i, j, FIELD_WIDTH);
            if (field[currentPosition] == NEW_SHAPE_PART) {
                partPositions[partIndex] = (Position) {j, i};
                ++partIndex;
            }
            if (field[currentPosition] == NEW_SHAPE_PIVOT) {
                pivotPosition = (Position) {j, i};
            }
        }
    }

    if (pivotPosition.x == -1) {
        return;
    }

    // Get rotated points
    int xOutOfBounds = 0;
    int yOutOfBounds = 0;
    for (int i = 0; i < 3; ++i) {
        newPartPositions[i] = rotatePoint(pivotPosition, partPositions[i], &xOutOfBounds, &yOutOfBounds);
    }
    newPartPositions[3] = pivotPosition;

    // Offset if out of playing field
    offsetPoints(xOutOfBounds, yOutOfBounds, newPartPositions);

    // Check if new positions are not intersecting with solid blocks
    for (int i = 0; i < 3; ++i) {
        int position = get1dIndex(newPartPositions[i].y, newPartPositions[i].x, FIELD_WIDTH);
        if (field[position] == SOLID) {
            return;
        }
    }

    // Erase old positions
    if (xOutOfBounds || yOutOfBounds) {
        int position = get1dIndex(pivotPosition.y, pivotPosition.x, FIELD_WIDTH);
        field[position] = EMPTY;
    }
    for (int i = 0; i < 3; ++i) {
        int position = get1dIndex(partPositions[i].y, partPositions[i].x, FIELD_WIDTH);
        field[position] = EMPTY;
    }

    // Write new positions
    int position;
    for (int i = 0; i < 4; ++i) {
        position = get1dIndex(newPartPositions[i].y, newPartPositions[i].x, FIELD_WIDTH);
        field[position] = NEW_SHAPE_PART;
    }
    field[position] = NEW_SHAPE_PIVOT;
}

bool isGameOver(const int *field) {
    for (int i = 0; i < FIELD_WIDTH; ++i) {
        if (field[i] == SOLID) return true;
    }

    return false;
}
