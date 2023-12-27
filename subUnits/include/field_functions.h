/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef FIELD_FUNCTIONS
#define FIELD_FUNCTIONS

#include <stdbool.h>
#include <time.h>
#include "tetris_constants.h"
#include "tetris_types.h"

void initializeField(int *field);

int get1dIndex(int row, int column, int width);

void addNewShapeToField(int *field, enum TetrisShapes shape);

void moveNewShape(int *field, enum Directions direction, bool *solid, unsigned int *score);

void dropNewShape(int *field, bool *solid, unsigned int *score);

void rotateShape(int *field);

bool isGameOver(const int *field);

#endif