/**
 * @author Dominik Milián
 * @Date 30.12.2023
 */

#include <scenes.h>

void leaderboard(SDL_Renderer *renderer, bool *quit, bool *menuRunning) {
    unsigned int numberOfScores;
    ScoreInfo *allScores = getAllScores(&numberOfScores);
    char **allScoresStr = malloc(numberOfScores * sizeof(char *));
    for (unsigned int i = 0; i < numberOfScores; ++i) {
        allScoresStr[i] = malloc((MAX_SCORE_LINE_LENGTH + 2) * sizeof(char));
        snprintf(allScoresStr[i], MAX_SCORE_LINE_LENGTH + 2, "%s: %d", allScores[i].playerName, allScores[i].score);
    }

    TTF_Font *leaderBoardFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, LEADERBOARD_FONT_PT_SIZE);

    SDL_Texture *leaderboardTableTexture = IMG_LoadTexture(renderer, LEADERBOARD_TABLE_PATH);
    SDL_Rect leaderboardTableRect;
    SDL_QueryTexture(leaderboardTableTexture, NULL, NULL, &leaderboardTableRect.w, &leaderboardTableRect.h);
    leaderboardTableRect.x = (WINDOW_WIDTH / 2) - (leaderboardTableRect.w / 2);
    leaderboardTableRect.y = 50;

    SDL_Texture **textures = malloc(numberOfScores * sizeof(SDL_Texture *));
    SDL_Rect rects[10];
    for (unsigned int i = 0; i < numberOfScores; ++i) {
        textures[i] = createTextureFromString(renderer, allScoresStr[i], leaderBoardFont, LEADERBOARD_RECORD_COLOR);
        SDL_QueryTexture(textures[i], NULL, NULL, &rects[i].w, &rects[i].h);
        rects[i].x = leaderboardTableRect.x + 20;
        rects[i].y = (int)(leaderboardTableRect.y + 80 + (i * 35));
    }

    SDL_Texture *backButton = IMG_LoadTexture(renderer, BACK_BUTTON_PATH);
    SDL_Rect backButtonRect;
    SDL_QueryTexture(backButton, NULL, NULL, &backButtonRect.w, &backButtonRect.h);
    backButtonRect.w /= 2;
    backButtonRect.h /= 2;
    backButtonRect.x = (WINDOW_WIDTH / 2) - (backButtonRect.w / 2);
    backButtonRect.y = leaderboardTableRect.y + leaderboardTableRect.h + 20;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    *quit = true;
                    running = false;
                    *menuRunning = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Point mousePoint;
                        SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
                        if (SDL_PointInRect(&mousePoint, &backButtonRect)) {
                            running = false;
                        }
                    }
                    break;
                }
            }
        }

        SDL_RenderCopy(renderer, leaderboardTableTexture, NULL, &leaderboardTableRect);
        SDL_RenderCopy(renderer, backButton, NULL, &backButtonRect);
        for (unsigned int i = 0; i < numberOfScores; ++i) {
            SDL_RenderCopy(renderer, textures[i], NULL, &rects[i]);
        }
        SDL_RenderPresent(renderer);
        clearScreen(renderer);
    }

    for (unsigned int i = 0; i < numberOfScores; ++i) {
        SDL_DestroyTexture(textures[i]);
        free(allScoresStr[i]);
    }
    free(textures);
    free(allScoresStr);

    TTF_CloseFont(leaderBoardFont);
    SDL_DestroyTexture(leaderboardTableTexture);
    SDL_DestroyTexture(backButton);
    free(allScores);
}

void menu(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName) {
    SDL_Texture *playButtonTexture = IMG_LoadTexture(renderer, PLAY_BUTTON_PATH);
    SDL_Texture *leaderboardButtonTexture = IMG_LoadTexture(renderer, LEADERBOARD_BUTTON_PATH);
    SDL_Texture *textBoxTexture = IMG_LoadTexture(renderer, TEXT_BOX_PATH);

    SDL_Rect playButtonRect;
    SDL_Rect leaderboardButtonRect;
    SDL_Rect textBoxRect;

    SDL_QueryTexture(playButtonTexture, NULL, NULL, &playButtonRect.w, &playButtonRect.h);
    SDL_QueryTexture(leaderboardButtonTexture, NULL, NULL, &leaderboardButtonRect.w, &leaderboardButtonRect.h);
    SDL_QueryTexture(textBoxTexture, NULL, NULL, &textBoxRect.w, &textBoxRect.h);

    playButtonRect.x = (WINDOW_WIDTH / 2) - (playButtonRect.w / 2);
    playButtonRect.y = 100;

    leaderboardButtonRect.x = (WINDOW_WIDTH / 2) - (leaderboardButtonRect.w / 2);
    leaderboardButtonRect.y = 250;

    textBoxRect.x = (WINDOW_WIDTH / 2) - (textBoxRect.w / 2);
    textBoxRect.y = 400;

    bool running = true;
    SDL_Event event;
    bool play = false;

    TTF_Font *playerNameFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, PLAYER_NAME_INPUT_PT_SIZE);

    SDL_Texture *playerNameInputTexture = createTextureFromString(renderer, playerName, playerNameFont,
                                                                  PLAYER_NAME_INPUT_COLOR);
    SDL_Rect playerNameInputRect;
    SDL_QueryTexture(playerNameInputTexture, NULL, NULL, &playerNameInputRect.w, &playerNameInputRect.h);
    playerNameInputRect.x = (WINDOW_WIDTH / 2) - (playerNameInputRect.w / 2);
    playerNameInputRect.y = textBoxRect.y + 10;

    SDL_StartTextInput();

    while (running && !play) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = false;
                    *quit = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Point mousePoint;
                        SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
                        if (SDL_PointInRect(&mousePoint, &playButtonRect)) {
                            play = true;
                            *scene = GAME;
                        } else if (SDL_PointInRect(&mousePoint, &leaderboardButtonRect)) {
                            leaderboard(renderer, quit, &running);
                        }
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        size_t length = strlen(playerName);
                        if (length == 0) {
                            break;
                        }

                        playerName[length - 1] = '\0';
                        SDL_DestroyTexture(playerNameInputTexture);
                        playerNameInputTexture = createTextureFromString(renderer, playerName, playerNameFont,
                                                                         PLAYER_NAME_INPUT_COLOR);
                        SDL_QueryTexture(playerNameInputTexture, NULL, NULL, &playerNameInputRect.w,
                                         &playerNameInputRect.h);
                        playerNameInputRect.x = (WINDOW_WIDTH / 2) - (playerNameInputRect.w / 2);
                    }

                    break;
                }
                case SDL_TEXTINPUT: {
                    if (strlen(playerName) == MAX_PLAYER_NAME_LENGTH) {
                        break;
                    }

                    strcat(playerName, event.text.text);
                    SDL_DestroyTexture(playerNameInputTexture);
                    playerNameInputTexture = createTextureFromString(renderer, playerName, playerNameFont,
                                                                     PLAYER_NAME_INPUT_COLOR);
                    SDL_QueryTexture(playerNameInputTexture, NULL, NULL, &playerNameInputRect.w,
                                     &playerNameInputRect.h);
                    playerNameInputRect.x = (WINDOW_WIDTH / 2) - (playerNameInputRect.w / 2);
                    break;
                }
            }
        }

        SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButtonRect);
        SDL_RenderCopy(renderer, leaderboardButtonTexture, NULL, &leaderboardButtonRect);
        SDL_RenderCopy(renderer, textBoxTexture, NULL, &textBoxRect);
        SDL_RenderCopy(renderer, playerNameInputTexture, NULL, &playerNameInputRect);
        SDL_RenderPresent(renderer);
        clearScreen(renderer);
    }

    SDL_DestroyTexture(playButtonTexture);
    SDL_DestroyTexture(textBoxTexture);
    SDL_DestroyTexture(playerNameInputTexture);
    SDL_StopTextInput();
}

void game(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName) {
    TTF_Font *scoreFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, SCORE_TEXT_FONT_PT_SIZE);
    TTF_Font *scoreValueFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, SCORE_VALUE_FONT_PT_SIZE);

    SDL_Texture *scoreStringTexture = createTextureFromString(renderer, "Score: ", scoreFont, SCORE_FONT_COLOR);
    SDL_Rect scoreStringRect;
    SDL_QueryTexture(scoreStringTexture, NULL, NULL, &scoreStringRect.w, &scoreStringRect.h);
    scoreStringRect.x = GRID_WIDTH_PX + 10;
    scoreStringRect.y = 20;

    SDL_Texture *scoreValueTexture = createTextureFromNumber(renderer, 0, scoreValueFont, SCORE_FONT_COLOR);
    SDL_Rect scoreValueRect;
    SDL_QueryTexture(scoreValueTexture, NULL, NULL, &scoreValueRect.w, &scoreValueRect.h);
    scoreValueRect.x = GRID_WIDTH_PX + 10;
    scoreValueRect.y = 20 + scoreStringRect.h;

    int *field = malloc(TOTAL_NUM_OF_CELLS * sizeof(int));
    initializeField(field);

    SDL_TimerID fallTimer = SDL_AddTimer(600, fallTimerCallback, NULL);

    int shapeRotation[SHAPE_COUNT];
    fillShapeRotation(shapeRotation);
    randomizeShapeRotation(shapeRotation);
    int nextShapeIndex = 0;

    SDL_Texture *nextShapeTexture = NULL;
    SDL_Rect nextShapeRect;
    nextShapeRect.x = GRID_WIDTH_PX + 10;
    nextShapeRect.y = scoreValueRect.y + 50;
    char nextShapePath[50] = {0};
    strcpy(nextShapePath, SHAPES_PATH_TEMPLATE);

    int nextShapeColorIndex = rand() % SHAPE_COUNT;
    int currentShapeColorIndex;

    SDL_Event event;
    bool running = true;
    SDL_Rect block = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    bool solid = true;

    while (running) {
        drawGridBackground(renderer);
        if (solid) {
            currentShapeColorIndex = nextShapeColorIndex;
            addNewShapeToField(field, shapeRotation[nextShapeIndex++]);
            solid = false;

            if (nextShapeIndex == SHAPE_COUNT) {
                randomizeShapeRotation(shapeRotation);
                nextShapeIndex = 0;
            }

            if (nextShapeTexture != NULL) {
                SDL_DestroyTexture(nextShapeTexture);
            }

            nextShapePath[strlen(nextShapePath) - 5] = (char) (shapeRotation[nextShapeIndex] + '0');
            nextShapeTexture = IMG_LoadTexture(renderer, nextShapePath);
            SDL_QueryTexture(nextShapeTexture, NULL, NULL, &nextShapeRect.w, &nextShapeRect.h);

            nextShapeColorIndex = rand() % SHAPE_COUNT;
            SDL_Color color = TETROMINO_COLORS[nextShapeColorIndex];
            SDL_SetTextureColorMod(nextShapeTexture, color.r, color.g, color.b);
        }

        handleEvents(&event, field, &running, &solid, &score, quit);
        handleBlockRendering(renderer, field, block, currentShapeColorIndex);

        drawGridLines(renderer);

        if (scoreChanged()) {
            scoreValueTexture = createTextureFromNumber(renderer, score, scoreValueFont, SCORE_FONT_COLOR);
            SDL_QueryTexture(scoreValueTexture, NULL, NULL, &scoreValueRect.w, NULL);
        }

        SDL_RenderCopy(renderer, nextShapeTexture, NULL, &nextShapeRect);
        SDL_RenderCopy(renderer, scoreValueTexture, NULL, &scoreValueRect);
        SDL_RenderCopy(renderer, scoreStringTexture, NULL, &scoreStringRect);
        SDL_RenderPresent(renderer);
        if (isGameOver(field)) {
            if (strlen(playerName) > 0) {
                saveScore(playerName);
            }

            *scene = GAME_OVER;
            running = false;
        }
        clearScreen(renderer);
    }

    SDL_RemoveTimer(fallTimer);
    SDL_DestroyTexture(scoreStringTexture);
    SDL_DestroyTexture(scoreValueTexture);
    TTF_CloseFont(scoreFont);
    TTF_CloseFont(scoreValueFont);
}

void gameOver(SDL_Renderer *renderer, bool *quit) {
    TTF_Font *gameOverFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, GAME_OVER_FONT_PT_SIZE);
    TTF_Font *scoreValueFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, GAME_OVER_SCORE_FONT_PT_SIZE);

    char scoreStr[30];
    snprintf(scoreStr, 30, "Score: %d", score);

    SDL_Texture *gameOverStringTexture = createTextureFromString(renderer, "GAME OVER", gameOverFont,
                                                                 GAME_OVER_FONT_COLOR);
    SDL_Rect gameOverStringRect;
    SDL_QueryTexture(gameOverStringTexture, NULL, NULL, &gameOverStringRect.w, &gameOverStringRect.h);
    gameOverStringRect.x = (WINDOW_WIDTH / 2) - (gameOverStringRect.w / 2);
    gameOverStringRect.y = (WINDOW_HEIGHT / 2) - (gameOverStringRect.h / 2);

    SDL_Texture *scoreStringTexture = createTextureFromString(renderer, scoreStr, scoreValueFont,
                                                              GAME_OVER_SCORE_FONT_COLOR);
    SDL_Rect scoreStringRect;
    SDL_QueryTexture(scoreStringTexture, NULL, NULL, &scoreStringRect.w, &scoreStringRect.h);
    scoreStringRect.x = (WINDOW_WIDTH / 2) - (scoreStringRect.w / 2);
    scoreStringRect.y = gameOverStringRect.y + gameOverStringRect.h + 5;

    TTF_CloseFont(gameOverFont);
    TTF_CloseFont(scoreValueFont);

    bool running = true;
    SDL_Event event;

    SDL_RenderCopy(renderer, gameOverStringTexture, NULL, &gameOverStringRect);
    SDL_RenderCopy(renderer, scoreStringTexture, NULL, &scoreStringRect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(gameOverStringTexture);
    SDL_DestroyTexture(scoreStringTexture);

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    *quit = true;
                    running = false;
                }
            }
        }
    }

    clearScreen(renderer);
}