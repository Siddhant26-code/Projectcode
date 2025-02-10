# Projectcode
Siddhant Sareen 202404039
Pearl Tarawat 202404029
Jay Patel 202404012
Nikhil Gupta 202404023


# Snake Game in C++

## Description
This is a simple console-based Snake game written in C++. The game is played within a terminal window where the player controls a snake using the keyboard. The goal is to eat the fruit and grow the snake without colliding with itself.

## Features
- Classic snake movement
- Randomly placed fruit
- Score tracking
- Walls wrap around (no collision with borders)

## Controls
- `W` - Move Up
- `S` - Move Down
- `A` - Move Left
- `D` - Move Right
- `X` - Quit the game

## How to Run
1. Compile the program using a C++ compiler (e.g., g++):
   ```sh
   g++ snake.cpp -o snake
   ```
2. Run the executable:
   ```sh
   ./snake  # On Linux/Mac
   snake.exe  # On Windows
   ```

## Dependencies
- Uses `<iostream>` for input/output
- Uses `<conio.h>` (only available on Windows for `_kbhit()` and `_getch()`). If using Linux, consider `ncurses` for input handling.

## Improvements
- Add a game-over screen with a restart option
- Implement a better input handling mechanism for cross-platform compatibility
- Introduce difficulty levels with speed variations

## License
This project is open-source and available under the MIT License.
