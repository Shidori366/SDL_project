/**
 * @author Dominik Milián
 * @Date 10.12.2023
 */

#include <tetris_constants.h>

const int STARTING_POSITION_HEIGHT = 4;
const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 20 + STARTING_POSITION_HEIGHT;
const int TOTAL_NUM_OF_CELLS = FIELD_WIDTH * FIELD_HEIGHT + FIELD_WIDTH * STARTING_POSITION_HEIGHT;

const int SIDEBAR_WIDTH = 300;

const int WINDOW_WIDTH = 300 + SIDEBAR_WIDTH;
const int WINDOW_HEIGHT = 720;

const int GRID_WIDTH_PX = WINDOW_WIDTH - SIDEBAR_WIDTH;

const int BLOCK_WIDTH = GRID_WIDTH_PX / FIELD_WIDTH;
const int BLOCK_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

const int SCORE_TEXT_FONT_PT_SIZE = 35;
const int SCORE_VALUE_FONT_PT_SIZE = 30;
const int GAME_OVER_FONT_PT_SIZE = 42;
const int GAME_OVER_SCORE_FONT_PT_SIZE = 22;
const int PLAYER_NAME_INPUT_PT_SIZE = 72;
const int LEADERBOARD_FONT_PT_SIZE = 25;

const char *ROBOTO_REGULAR_FONT_PATH = "../resources/fonts/Roboto-Regular.ttf";
const char *SCORES_FILE_PATH = "../resources/scores.txt";
const char *PLAY_BUTTON_PATH = "../resources/images/menu/play_button.png";
const char *BACK_BUTTON_PATH = "../resources/images/menu/back_button.png";
const char *LEADERBOARD_BUTTON_PATH = "../resources/images/menu/leaderboard_button.png";
const char *LEADERBOARD_TABLE_PATH = "../resources/images/menu/leaderboard_table.png";
const char *TEXT_BOX_PATH = "../resources/images/menu/text_box.png";
const char *SHAPES_PATH_TEMPLATE = "../resources/images/shapes/0.png";

const SDL_Color SCORE_FONT_COLOR = {
        255,
        255,
        255,
        0
};
const SDL_Color GAME_OVER_FONT_COLOR = {
        255,
        0,
        0,
        0
};

const SDL_Color GAME_OVER_SCORE_FONT_COLOR = {
        255,
        255,
        255,
        0
};

const SDL_Color PLAYER_NAME_INPUT_COLOR = {
        255,
        255,
        255,
        0
};

const SDL_Color LEADERBOARD_RECORD_COLOR = {
        255,
        255,
        255,
        0
};

const SDL_Color GRID_BACKGROUND_COLOR = {
        25,
        25,
        25,
        255
};

const SDL_Color GRID_LINES_COLOR = {
        0,
        0,
        0,
        255
};

const SDL_Color CLEAR_COLOR = {
        0,
        0,
        0,
        255
};

const SDL_Color SOLID_BLOCK_COLOR = {
        200,
        200,
        200,
        255
};

const int shapeWidthArr[SHAPE_COUNT] = {
        1, 2, 3, 2, 2, 3, 3
};

const SDL_Color TETROMINO_COLORS[] = {
        {202, 5,   5,   255},
        {130, 202, 5,   255},
        {5,   202, 193, 255},
        {5,   202, 17,  255},
        {219, 231, 33,  255},
        {118, 5,   202, 255},
        {202, 5,   85,  255}
};