/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "tetris_constants.h"
#include "field_functions.h"
#include "sdl_functions.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    srand(time(NULL));

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation error\n");
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    int *field = malloc(TOTAL_NUM_OF_CELLS * sizeof(int));
    initializeField(field);
    addNewShapeToField(field, SKEW_TETROMINO);

    SDL_Event event;
    int running = 1;
    int currentNewShapeColorIndex;
    SDL_Rect block = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    bool solid = false;

    while (running) {
        drawGridBackground(renderer);
        if (solid) {
            addNewShapeToField(field, rand() % (SHAPE_COUNT));
            currentNewShapeColorIndex = rand() % SHAPE_COUNT;
            solid = false;
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
                        moveNewShape(field, LEFT, &solid);
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        moveNewShape(field, RIGHT, &solid);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        moveNewShape(field, DOWN, &solid);
                    }
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        dropNewShape(field, &solid);
                    }
                }
            }
        }

        for (int i = 0; i < FIELD_HEIGHT; ++i) {
            for (int j = 0; j < FIELD_WIDTH; ++j) {
                block.x = j * BLOCK_WIDTH;
                block.y = i * BLOCK_HEIGHT;
                switch (field[getPosition(i, j, FIELD_WIDTH)]) {
                    case EMPTY: {
                        continue;
                    }
                    case SOLID: {
                        renderBlock(renderer, block, SOLID_BLOCK_COLOR);

                        continue;
                    }
                    case NEW_SHAPE_PART: {
                        renderBlock(renderer, block, TETROMINO_COLORS[currentNewShapeColorIndex]);

                        continue;
                    }
                }
            }
        }

        drawGridLines(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
        clearScreen(renderer);
    }

    return 0;
}
