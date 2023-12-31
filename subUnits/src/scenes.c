/**
 * @author Dominik Milián
 * @Date 30.12.2023
 */

#include <scenes.h>

void menu(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName) {
    SDL_Texture *playButtonTexture = IMG_LoadTexture(renderer, PLAY_BUTTON_PATH);
    SDL_Texture *textBoxTexture = IMG_LoadTexture(renderer, TEXT_BOX_PATH);

    SDL_Rect playButtonRect;
    SDL_Rect textBoxRect;

    SDL_QueryTexture(playButtonTexture, NULL, NULL, &playButtonRect.w, &playButtonRect.h);
    SDL_QueryTexture(textBoxTexture, NULL, NULL, &textBoxRect.w, &textBoxRect.h);

    playButtonRect.x = (WINDOW_WIDTH / 2) - (playButtonRect.w / 2);
    playButtonRect.y = 100;

    textBoxRect.x = (WINDOW_WIDTH / 2) - (textBoxRect.w / 2);
    textBoxRect.y = 300;

    bool running = true;
    SDL_Event event;
    bool play = false;

    TTF_Font *playerNameFont = TTF_OpenFont(ROBOTO_REGULAR_FONT_PATH, PLAYER_NAME_INPUT_PT_SIZE);

    SDL_Texture *playerNameInputTexture = createTextureFromString(renderer, playerName, playerNameFont,
                                                                  PLAYER_NAME_INPUT_COLOR);
    SDL_Rect playerNameInputRect;
    SDL_QueryTexture(playerNameInputTexture, NULL, NULL, &playerNameInputRect.w, &playerNameInputRect.h);
    playerNameInputRect.x = textBoxRect.x + 10;
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
                    break;
                }
            }
        }

        SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButtonRect);
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

    SDL_Event event;
    bool running = true;
    int currentNewShapeColorIndex;
    SDL_Rect block = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    bool solid = true;

    while (running) {
        drawGridBackground(renderer);
        if (solid) {
            addNewShapeToField(field, shapeRotation[nextShapeIndex++]);
            currentNewShapeColorIndex = rand() % SHAPE_COUNT;
            solid = false;

            if (nextShapeIndex == SHAPE_COUNT) {
                randomizeShapeRotation(shapeRotation);
                nextShapeIndex = 0;
            }
        }

        handleEvents(&event, field, &running, &solid, &score, quit);
        handleBlockRendering(renderer, field, block, currentNewShapeColorIndex);

        drawGridLines(renderer);

        if (scoreChanged()) {
            scoreValueTexture = createTextureFromNumber(renderer, score, scoreValueFont, SCORE_FONT_COLOR);
            SDL_QueryTexture(scoreValueTexture, NULL, NULL, &scoreValueRect.w, NULL);
        }

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