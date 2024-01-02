/**
 * @author Dominik Milián
 * @Date 10.12.2023
 * @brief File containing functions for manipulating state of game
 */

#ifndef FIELD_FUNCTIONS
#define FIELD_FUNCTIONS

#include <stdbool.h>
#include <time.h>
#include <tetris_constants.h>
#include <tetris_types.h>

/**
 * Initialize field with EMPTY state.
 * @param field Array of numbers representing current state of game.
 * */
void initializeField(int *field);

/**
 * Translate 2D indexes into 1D index.
 * @param row Vertical coordinate.
 * @param column Horizontal coordinate.
 * @param width Width of the field.
 * @return Number representing 1D index.
 */
int get1dIndex(int row, int column, int width);

/**
 * Add new shape to a random position at the start of the field.
 * @param field Array of numbers representing current state of game.
 * @param shape Shape to be added. Valid values are shown in TetrisShapes ENUM.
 */
void addNewShapeToField(int *field, enum TetrisShapes shape);

/**
 * Move currently falling shape in a certain direction.
 * @param field Array of numbers representing current state of game.
 * @param direction
 * @param solid Bool representing if falling shape became solid.
 * @param score Pointer to number representing current score.
 */
void moveNewShape(int *field, enum Directions direction, bool *solid, unsigned int *score);

/**
 * Move falling shape down until collision occurs.
 * @param field Array of numbers representing current state of game.
 * @param solid Bool representing if falling shape became solid.
 * @param score Pointer to number representing current score.
 */
void dropNewShape(int *field, bool *solid, unsigned int *score);

/**
 * @brief Rotate falling shape by 90 degrees.
 *
 * This function will rotate currently falling shape in case no collision will occur.
 * In case rotated shape will get out of field bounds it will be moved back into field.
 * @param field Array of numbers representing current state of game.
 */
void rotateShape(int *field);

/**
 * @brief Determine game over.
 *
 * This function will check for solid blocks in first row.
 * In case there is any solid block the game is over.
 * @param field
 * @return Bool representing if game is over.
 */
bool isGameOver(const int *field);

#endif