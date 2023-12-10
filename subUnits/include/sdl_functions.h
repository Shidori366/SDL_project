/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef SDL_FUNCTIONS
#define SDL_FUNCTIONS

#include <SDL.h>
#include "tetris_constants.h"

void drawGridBackground(SDL_Renderer *renderer);
void drawGridLines(SDL_Renderer *renderer);
void kill(SDL_Window *window, SDL_Renderer *renderer);
void clearScreen(SDL_Renderer *renderer);
void renderBlock(SDL_Renderer *renderer, SDL_Rect block, SDL_Color color);

#endif