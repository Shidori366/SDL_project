/**
 * @author Dominik Milián
 * @Date 30.12.2023
 * @brief File containing functions to work with shape rotation.
 */

#ifndef SDL_PROJECT_SHAPE_ROTATION_FUNCTIONS_H
#define SDL_PROJECT_SHAPE_ROTATION_FUNCTIONS_H

#include <tetris_constants.h>

/**
 * Fill shape rotation with valid values.
 * @param shapeRotation Array of numbers representing shape rotation.
 */
void fillShapeRotation(int *shapeRotation);

/**
 * Randomize shape rotation
 * @param shapeRotation Array of numbers representing shape rotation.
 */
void randomizeShapeRotation(int *shapeRotation);

#endif //SDL_PROJECT_SHAPE_ROTATION_FUNCTIONS_H
