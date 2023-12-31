/**
 * @author Dominik Milián
 * @Date 30.12.2023
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

void menu(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName);

void game(SDL_Renderer *renderer, enum Scenes *scene, bool *quit, char *playerName);

void gameOver(SDL_Renderer *renderer, bool *quit);

#endif //SDL_PROJECT_SCENES_H


