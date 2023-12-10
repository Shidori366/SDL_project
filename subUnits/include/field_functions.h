/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef FIELD_FUNCTIONS
#define FIELD_FUNCTIONS

#include "tetris_constants.h"

void initializeField(int *field);
int getPosition(int row, int column, int width);
void addNewShapeToField(int *field, enum TetrisShapes shape);

#endif