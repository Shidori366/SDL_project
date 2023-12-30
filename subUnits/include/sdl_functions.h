/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#ifndef SDL_FUNCTIONS
#define SDL_FUNCTIONS

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <tetris_constants.h>
#include <stdbool.h>
#include <field_functions.h>

void drawGridBackground(SDL_Renderer *renderer);

void drawGridLines(SDL_Renderer *renderer);

void kill(SDL_Window *window, SDL_Renderer *renderer);

void clearScreen(SDL_Renderer *renderer);

void renderBlock(SDL_Renderer *renderer, SDL_Rect block, SDL_Color color);

void handleEvents(SDL_Event *event, int *field, SDL_Renderer *renderer, SDL_Window *window, bool *running, bool *solid,
                  unsigned int *score);

void handleBlockRendering(SDL_Renderer *renderer, const int *field, SDL_Rect block, int currentNewShapeColorIndex);

SDL_Texture *createTextureFromString(SDL_Renderer *renderer, char *str, TTF_Font *font, SDL_Color color);

SDL_Texture *createTextureFromNumber(SDL_Renderer *renderer, long number, TTF_Font *font, SDL_Color color);

#endif