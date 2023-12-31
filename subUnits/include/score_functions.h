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

typedef struct ScoreInfo{
    char playerName[MAX_PLAYER_NAME_LENGTH];
    int score;
} ScoreInfo;

bool scoreChanged();

ScoreInfo *getAllScores(unsigned int *numberOfScores);

void saveScore(char *playerName);

#endif //SDL_PROJECT_SCORE_FUNCTIONS_H
