//
// Created by shidori on 12/30/23.
//

#include <score_functions.h>

bool scoreChanged(const unsigned int score) {
    static unsigned int lastScore = 0;

    if (lastScore == score) {
        return false;
    }

    lastScore = score;
    return true;
}

void cleanScoreFile() {
    FILE *f = fopen(SCORES_FILE_PATH, "wr");
    int maxLineLength = MAX_PLAYER_NAME_LENGTH + 21;
    char lines[11][maxLineLength];
    unsigned int linesCount = 0;

    for (int i = 0; i < 11; ++i) {
        fgets(lines[i], maxLineLength, f);
    }

    fclose(f);
}

/*
 * 1. add score into file
 * 2. remove from file all which doesn't belong into top 10
 * */
void addScore(char *playerName, const unsigned int score) {
    FILE *f = fopen(SCORES_FILE_PATH, "a");

    fprintf(f, "%s|%d\n", playerName, score);

    fclose(f);

    cleanScoreFile();
}