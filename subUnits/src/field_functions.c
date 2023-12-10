/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include "../include/field_functions.h"

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
            int startPos = FIELD_WIDTH / 2 - 2;
            for (int i = 0; i < 4; ++i) {
                field[startPos + i] = NEW_SHAPE_PART;
            }

            return;
        }
        case SQUARE_TETROMINO: {
            int startPos = FIELD_WIDTH / 2 - 1;
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case T_TETROMINO: {
            int startPos = FIELD_WIDTH / 2 - 1;
            field[startPos] = NEW_SHAPE_PART;
            field[startPos + 1] = NEW_SHAPE_PART;
            field[startPos + 2] = NEW_SHAPE_PART;
            field[getPosition(1, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case L_TETROMINO: {
            int startPos = FIELD_WIDTH / 2 - 1;
            field[startPos] = NEW_SHAPE_PART;
            field[getPosition(1, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(2, startPos, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(2, startPos + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
        case SKEW_TETROMINO: {
            int startPos = getPosition(1, FIELD_WIDTH / 2 - 1, FIELD_WIDTH);
            field[startPos] = NEW_SHAPE_PART;
            field[startPos+1] = NEW_SHAPE_PART;
            field[getPosition(0, FIELD_WIDTH / 2, FIELD_WIDTH)] = NEW_SHAPE_PART;
            field[getPosition(0, FIELD_WIDTH / 2 + 1, FIELD_WIDTH)] = NEW_SHAPE_PART;

            return;
        }
    }
}