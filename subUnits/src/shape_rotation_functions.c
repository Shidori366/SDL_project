//
// Created by shidori on 12/30/23.
//

#include <shape_rotation_functions.h>

void fillShapeRotation(int *shapeRotation) {
    for (int i = 0; i < SHAPE_COUNT; ++i) {
        shapeRotation[i] = i;
    }
}

void randomizeShapeRotation(int *shapeRotation) {
    for (int i = 0; i < SHAPE_COUNT; ++i) {
        int random = rand() % SHAPE_COUNT;
        int temp = shapeRotation[i];
        shapeRotation[i] = shapeRotation[random];
        shapeRotation[random] = temp;
    }
}