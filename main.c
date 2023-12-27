/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "tetris_constants.h"
#include "field_functions.h"
#include "sdl_functions.h"

Uint32 callback(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userEvent;

    userEvent.type = SDL_USEREVENT;
    userEvent.code = 0;
    userEvent.data1 = NULL;
    userEvent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);

    return interval;
}

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

bool scoreChanged(const unsigned int *score) {
    static unsigned int lastScore = 0;

    if (lastScore == *score) {
        return false;
    }

    lastScore = *score;
    return true;
}

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

    SDL_TimerID fallTimer = SDL_AddTimer(600, callback, NULL);

    int shapeRotation[SHAPE_COUNT];
    fillShapeRotation(shapeRotation);
    randomizeShapeRotation(shapeRotation);
    int nextShapeIndex = 0;

    SDL_Event event;
    int running = 1;
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

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    kill(window, renderer);
                    running = 0;

                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_UP) {
                        rotateShape(field);
                    }
                    if (event.key.keysym.sym == SDLK_LEFT) {
                        moveNewShape(field, LEFT, &solid, &score);
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        moveNewShape(field, RIGHT, &solid, &score);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        moveNewShape(field, DOWN, &solid, &score);
                    }
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        dropNewShape(field, &solid, &score);
                    }
                }
                case SDL_USEREVENT: {
                    if (event.user.code == 0) {
                        moveNewShape(field, DOWN, &solid, &score);
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < FIELD_HEIGHT; ++i) {
            for (int j = 0; j < FIELD_WIDTH; ++j) {
                block.x = j * BLOCK_WIDTH;
                block.y = i * BLOCK_HEIGHT;
                switch (field[get1dIndex(i, j, FIELD_WIDTH)]) {
                    case EMPTY: {
                        continue;
                    }
                    case SOLID: {
                        renderBlock(renderer, block, SOLID_BLOCK_COLOR);

                        continue;
                    }
                    case NEW_SHAPE_PART: {}
                    case NEW_SHAPE_PIVOT: {
                        renderBlock(renderer, block, TETROMINO_COLORS[currentNewShapeColorIndex]);

                        continue;
                    }
                }
            }
        }

        drawGridLines(renderer);

        if (scoreChanged(&score)) {
            scoreValueTexture = createTextureFromNumber(renderer, score, scoreValueFont, SCORE_FONT_COLOR);
            SDL_QueryTexture(scoreValueTexture, NULL, NULL, &scoreValueRect.w, NULL);
        }

        SDL_RenderCopy(renderer, scoreValueTexture, NULL, &scoreValueRect);
        SDL_RenderCopy(renderer, scoreStringTexture, NULL, &scoreStringRect);
        SDL_RenderPresent(renderer);
        // TODO: implement game over screen
        if (isGameOver(field)) {
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
