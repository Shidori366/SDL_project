/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "subUnits/include/tetris_constants.h"
#include "subUnits/include/field_functions.h"
#include "subUnits/include/sdl_functions.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

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
    addNewShapeToField(field, SQUARE_TETROMINO);

    SDL_Event event;
    int running = 1;
    SDL_Rect block = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};

    while (running) {
        drawGridBackground(renderer);

        // TODO: Game logic
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    kill(window, renderer);
                    running = 0;

                    break;
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
                        renderBlock(renderer, block, (SDL_Color) {54, 175, 153, 255});

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
