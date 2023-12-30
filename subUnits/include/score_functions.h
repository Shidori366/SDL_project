//
// Created by shidori on 12/30/23.
//

#ifndef SDL_PROJECT_SCORE_FUNCTIONS_H
#define SDL_PROJECT_SCORE_FUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <tetris_constants.h>

bool scoreChanged(unsigned int score);

void addScore(char *playerName, unsigned int score);

#endif //SDL_PROJECT_SCORE_FUNCTIONS_H
