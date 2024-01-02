/**
 * @author Dominik Milián
 * @Date 10.12.2023
 * @brief File containing functions to automate common SDL actions.
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

/**
 * Paint screen with black color.
 * @param renderer
 */
void clearScreen(SDL_Renderer *renderer);

/**
 * Render block at certain position.
 * @param renderer
 * @param block SDL_Rect representing properties of block which will be drawn.
 * @param color Color with which the block will be painted.
 */
void renderBlock(SDL_Renderer *renderer, SDL_Rect block, SDL_Color color);

/**
 * Handle all relevant user events.
 * @param event Pointer to event variable.
 * @param field Array of numbers representing current state of game.
 * @param running Pointer to bool which tells if game loop should end.
 * @param solid Bool representing if falling shape became solid.
 * @param score Pointer to number representing current score.
 * @param quit Pointer to quit variable so user is able to quit game early.
 */
void handleEvents(SDL_Event *event, int *field, bool *running, bool *solid, unsigned int *score, bool *quit);

/**
 *
 * @param renderer
 * @param field Array of numbers representing current state of game.
 * @param block SDL_Rect representing properties of block which will be used to draw all blocks.
 * @param currentNewShapeColorIndex Index of color by which new shape blocks will be painted.
 */
void handleBlockRendering(SDL_Renderer *renderer, const int *field, SDL_Rect block, int currentNewShapeColorIndex);

/**
 * Create texture from string.
 * @param renderer
 * @param str String from which texture will be created.
 * @param font Font used to create the texture.
 * @param color Color of the resulting texture.
 * @return Created texture.
 */
SDL_Texture *createTextureFromString(SDL_Renderer *renderer, char *str, TTF_Font *font, SDL_Color color);

/**
 * Create texture from number.
 * @param renderer
 * @param number Number from which texture will be created.
 * @param font Font used to create the texture.
 * @param color Color of the resulting texture.
 * @return Created texture.
 */
SDL_Texture *createTextureFromNumber(SDL_Renderer *renderer, long number, TTF_Font *font, SDL_Color color);

#endif