/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include "../include/sdl_functions.h"

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

void kill(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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