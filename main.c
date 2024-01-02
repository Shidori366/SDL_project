/**
 * @author Dominik Milián
 * @Date 10.12.2023
 * @brief File containing starting point of this project.
 */

#include <SDL2/SDL.h>
#include <tetris_constants.h>
#include <scenes.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    srand(time(NULL));

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation error\n");
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool quit = false;
    enum Scenes scene = MENU;
    char playerName[MAX_PLAYER_NAME_LENGTH+1] = {0};

    while(!quit) {
        switch (scene) {
            case MENU: {
                menu(renderer, &scene, &quit, playerName);
                break;
            }
            case GAME: {
                game(renderer, &scene, &quit, playerName);
                break;
            }
            case GAME_OVER: {
                gameOver(renderer, &quit);
                break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
