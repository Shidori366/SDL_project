/**
 * @author Dominik Milián
 * @Date 30.12.2023
 */

#include <score_functions.h>

unsigned int score = 0;

bool scoreChanged() {
    static unsigned int lastScore = 0;

    if (lastScore == score) {
        return false;
    }

    lastScore = score;
    return true;
}

ScoreInfo parseScore(char *str) {
    ScoreInfo scoreInfo;
    strcpy(scoreInfo.playerName, strtok(str, "|"));
    scoreInfo.score = atoi(strtok(NULL, "\n"));
    return scoreInfo;
}

ScoreInfo *getAllScores(unsigned int *numberOfScores) {
    FILE *f = fopen(SCORES_FILE_PATH, "r");
    ScoreInfo *scores = malloc(10 * sizeof(ScoreInfo));
    char line[MAX_SCORE_LINE_LENGTH] = {0};
    *numberOfScores = 0;

    for (int i = 0; i < 10; ++i) {
        if (fgets(line, MAX_SCORE_LINE_LENGTH, f) == NULL) {
            break;
        }
        scores[i] = parseScore(line);
        (*numberOfScores)++;
    }

    fclose(f);
    return scores;
}

void sortScoreArray(ScoreInfo *scoreArray, unsigned int size) {
    for (unsigned int i = 0; i < size - 1; ++i) {
        for (unsigned int j = 0; j < size - i - 1; ++j) {
            if (scoreArray[j].score < scoreArray[j + 1].score) {
                ScoreInfo temp = scoreArray[j];
                scoreArray[j] = scoreArray[j + 1];
                scoreArray[j + 1] = temp;
            }
        }
    }
}

void cleanScoreFile() {
    FILE *f = fopen(SCORES_FILE_PATH, "r");
    char line[MAX_SCORE_LINE_LENGTH] = {0};
    ScoreInfo scoreArr[11];
    unsigned int recordCount = 0;

    for (int i = 0; i < 11; ++i) {
        if (fgets(line, MAX_SCORE_LINE_LENGTH, f) == NULL) {
            break;
        }

        recordCount++;

        scoreArr[i] = parseScore(line);

    }
    fclose(f);

    sortScoreArray(scoreArr, recordCount);

    f = fopen(SCORES_FILE_PATH, "w");

    for (unsigned int i = 0; i < recordCount; ++i) {
        if (i == 10) {
            break;
        }
        fprintf(f, "%s|%d\n", scoreArr[i].playerName, scoreArr[i].score);
    }

    fclose(f);
}

void saveScore(char *playerName) {
    FILE *f = fopen(SCORES_FILE_PATH, "a");
    fprintf(f, "%s|%d\n", playerName, score);
    fclose(f);

    cleanScoreFile();
}