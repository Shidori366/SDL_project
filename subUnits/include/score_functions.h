/**
 * @author Dominik Milián
 * @Date 30.12.2023
 * @brief File containing functions to manipulate with score.
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

/**
 * Check if score changed.
 * @return Bool representing if score changed or not.
 */
bool scoreChanged();

/**
 * Get all scores currently saved.
 * @param numberOfScores Pointer to number variable,
 * where number of currently saved scores will be written.
 * @return Array of saved scores represented by ScoreInfo struct.
 */
ScoreInfo *getAllScores(unsigned int *numberOfScores);

/**
 * Save score.
 * @param playerName player name under which score will be saved.
 */
void saveScore(char *playerName);

#endif //SDL_PROJECT_SCORE_FUNCTIONS_H
