/**
 * @author Dominik Milián
 * @Date 30.12.2023
 * @brief File containing scenes between which game will switch.
 */

#ifndef SDL_PROJECT_SCENES_H
#define SDL_PROJECT_SCENES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <tetris_constants.h>
#include <sdl_functions.h>
#include <score_functions.h>
#include <timer_callbacks.h>
#include <shape_rotation_functions.h>
#include <field_functions.h>

/**
 * Show game menu scene.
 * @param renderer
 * @param scene Pointer to scene variable to switch between scenes.
 * @param quit Pointer to quit variable so user is able to quit game early.
 * @param playerName Buffer into which player name will be written.
 */
void menu(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName);

/**
 * Snow game scene
 * @param renderer
 * @param scene Pointer to scene variable to switch between scenes.
 * @param quit Pointer to quit variable so user is able to quit game early.
 * @param playerName Player name string.
 */
void game(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName);

/**
 * Show game over Scene.
 * @param renderer
 * @param quit Pointer to quit variable so user is able to quit game early.
 */
void gameOver(SDL_Renderer *renderer, bool *quit);

#endif //SDL_PROJECT_SCENES_H


