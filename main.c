/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "tetris_constants.h"
#include "field_functions.h"
#include "sdl_functions.h"
#include "tetris_types.h"

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

//    SDL_TimerID fallTimer = SDL_AddTimer(1200, callback, NULL);

    SDL_Event event;
    int running = 1;
    SDL_Rect block = {0, 0, BLOCK_WIDTH, BLOCK_HEIGHT};
    bool solid = true;

    while (running) {
        drawGridBackground(renderer);
        if (solid) {
            addNewShapeToField(field, rand() % (SHAPE_COUNT));
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
                case SDL_USEREVENT: {
                    if (event.user.code == 0) {
                        moveNewShape(field, DOWN, &solid);
                    }
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
                    case NEW_SHAPE_PART: {}
                    case NEW_SHAPE_PIVOT: {
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

//    SDL_RemoveTimer(fallTimer);

    return 0;
}
