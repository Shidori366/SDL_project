cmake_minimum_required(VERSION 3.25)
project(SDL_project C)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/subUnits/include)

set(SOURCE_FILES
        main.c
        subUnits/src/field_functions.c
        subUnits/src/sdl_functions.c
        subUnits/src/tetris_constants.c)

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2)