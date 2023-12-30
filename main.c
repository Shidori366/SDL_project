/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <tetris_constants.h>
#include <field_functions.h>
#include <sdl_functions.h>
#include <shape_rotation_functions.h>
#include <timer_callbacks.h>
#include <score_functions.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    srand(time(NULL));

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation error\n");
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

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
    unsigned int score = 0;
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

        handleEvents(&event, field, renderer, window, &running, &solid, &score);
        handleBlockRendering(renderer, field, block, currentNewShapeColorIndex);

        drawGridLines(renderer);

        if (scoreChanged(score)) {
            scoreValueTexture = createTextureFromNumber(renderer, score, scoreValueFont, SCORE_FONT_COLOR);
            SDL_QueryTexture(scoreValueTexture, NULL, NULL, &scoreValueRect.w, NULL);
        }

        SDL_RenderCopy(renderer, scoreValueTexture, NULL, &scoreValueRect);
        SDL_RenderCopy(renderer, scoreStringTexture, NULL, &scoreStringRect);
        SDL_RenderPresent(renderer);
        // TODO: implement game over screen
        if (isGameOver(field)) {
            addScore("test2", score);

            running = 0;
        }
        clearScreen(renderer);
    }

    SDL_RemoveTimer(fallTimer);
    TTF_CloseFont(scoreFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
