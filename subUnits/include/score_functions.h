/**
 * @author Dominik Milián
 * @Date 30.12.2023
 */

#ifndef SDL_PROJECT_SCORE_FUNCTIONS_H
#define SDL_PROJECT_SCORE_FUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <tetris_constants.h>

extern unsigned int score;

bool scoreChanged();

void saveScore(char *playerName);

#endif //SDL_PROJECT_SCORE_FUNCTIONS_H
