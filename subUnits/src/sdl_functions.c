/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <sdl_functions.h>

void drawGridBackground(SDL_Renderer *renderer) {
    SDL_Rect gridRect = {0, 0, GRID_WIDTH_PX, WINDOW_HEIGHT};
    SDL_SetRenderDrawColor(renderer,
                           GRID_BACKGROUND_COLOR.r,
                           GRID_BACKGROUND_COLOR.g,
                           GRID_BACKGROUND_COLOR.b,
                           GRID_BACKGROUND_COLOR.a);
    SDL_RenderFillRect(renderer, &gridRect);
}

void drawGridLines(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer,
                           GRID_LINES_COLOR.r,
                           GRID_LINES_COLOR.g,
                           GRID_LINES_COLOR.b,
                           GRID_LINES_COLOR.a);
    for (int i = 1; i < GRID_WIDTH_PX / BLOCK_WIDTH; ++i) {
        int x = i * BLOCK_WIDTH;
        SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }
    for (int i = 1; i < WINDOW_HEIGHT / BLOCK_HEIGHT; ++i) {
        int y = i * BLOCK_HEIGHT;
        SDL_RenderDrawLine(renderer, 0, y, GRID_WIDTH_PX, y);
    }
}

void clearScreen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer,
                           CLEAR_COLOR.r,
                           CLEAR_COLOR.g,
                           CLEAR_COLOR.b,
                           CLEAR_COLOR.a);
    SDL_RenderClear(renderer);
}

void renderBlock(SDL_Renderer *renderer, SDL_Rect block, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);
    SDL_RenderFillRect(renderer, &block);
}

void handleEvents(SDL_Event *event, int *field, bool *running, bool *solid, unsigned int *score, bool *quit) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT: {
                *quit = true;
                *running = false;

                break;
            }
            case SDL_KEYDOWN: {
                if (event->key.keysym.sym == SDLK_UP) {
                    rotateShape(field);
                }
                if (event->key.keysym.sym == SDLK_LEFT) {
                    moveNewShape(field, LEFT, solid, score);
                }
                if (event->key.keysym.sym == SDLK_RIGHT) {
                    moveNewShape(field, RIGHT, solid, score);
                }
                if (event->key.keysym.sym == SDLK_DOWN) {
                    moveNewShape(field, DOWN, solid, score);
                }
                if (event->key.keysym.sym == SDLK_SPACE) {
                    dropNewShape(field, solid, score);
                }
            }
            case SDL_USEREVENT: {
                if (event->user.code == 0) {
                    moveNewShape(field, DOWN, solid, score);
                }
                break;
            }
        }
    }
}

void handleBlockRendering(SDL_Renderer *renderer, const int *field, SDL_Rect block, int currentNewShapeColorIndex) {
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
                case NEW_SHAPE_PART: {
                }
                case NEW_SHAPE_PIVOT: {
                    renderBlock(renderer, block, TETROMINO_COLORS[currentNewShapeColorIndex]);

                    continue;
                }
            }
        }
    }
}

SDL_Texture *createTextureFromString(SDL_Renderer *renderer, char *str, TTF_Font *font, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, str, color);
    return SDL_CreateTextureFromSurface(renderer, surface);
}

SDL_Texture *createTextureFromNumber(SDL_Renderer *renderer, long number, TTF_Font *font, SDL_Color color) {
    char numStrBuffer[20];
    snprintf(numStrBuffer, 30, "%ld", number);
    SDL_Surface *surface = TTF_RenderText_Solid(font, numStrBuffer, color);
    return SDL_CreateTextureFromSurface(renderer, surface);
}