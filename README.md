# Tetris
Tetris is a game created by Alexey Pajitnov in 1985.  
This repository contains very fundamental clone of this game.
All mechanics from original Tetris should work in this version very similarly. 

## Dependencies
- SDL2
- SDL2 image
- SDL2 ttf

## Build instructions:
1. in root folder `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

## Controls
`Arrow Right`, `Arrow Left`, `Arrow Down` - Move falling shape  
`Arrow Up` - Rotate falling shape  
`Space` - Drop falling shape

## Project Structure
- **resources** - folder containing all resources this project uses, including
                  all fonts, images and file with scores.
- **subUnits** 
    + **include** - folder containing all headers meant to be included
    + **src** - folder containing implementations of headers in include folder
