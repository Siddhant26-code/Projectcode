# Snake Game

## Description
This is the classic Snake Game. The game runs in the terminal and allows players to control a snake that moves around the screen, consuming food and growing in size while avoiding collisions with the walls and itself. The game maintains a high score record too. Our game is designed as per Windows ecosystem.

## Features
- **Smooth Gameplay**: The snake moves continuously in the chosen direction.
- **Expanded Play Area**: The board width has been increased to 70 for better gameplay.
- **Food Mechanics**: Randomly generated food that increases the snake's length when consumed.
- **Collision Detection**: The game ends when the snake collides with itself or the wall.
- **High Score Tracking**: The highest score is stored in a file (`highscore.txt`) and displayed at the end of the game.
- **Pause Functionality**: Press `P` to pause or resume the game.
- **Bordered Play Area**: The snake is confined within a bordered area for a structured gameplay experience.

## Controls
- `W` / `Arrow Up` → Move Up
- `S` / `Arrow Down` → Move Down
- `A` / `Arrow Left` → Move Left
- `D` / `Arrow Right` → Move Right
- `P` → Pause/Resume Game

## How to Run the Game
1. Ensure you have a **C++ compiler** installed (such as MinGW for Windows or g++ for Linux/Mac).
2. Copy the source code into a `.cpp` file (e.g., `snake_game.cpp`).
3. Open a terminal or command prompt in the directory containing the file.
4. Compile the program using the following command:
   ```
   g++ snake_game.cpp -o snake_game.exe
   ```
5. Run the compiled program:
   ```
   ./snake_game.exe  (Windows)
   ./snake_game      (Linux/Mac)
   ```

## Prerequisites
- Windows OS (for `windows.h` functions such as `SetConsoleCursorPosition` and `Sleep`).
- A C++ compiler like MinGW (`g++`).

## Game Mechanics
1. The snake starts at the center of the board with an initial length of 3.
2. It moves automatically in the last given direction(except during the start of a new game).
3. When the snake eats food (`X`), it grows in length and the score increases.
4. If the snake hits the border (`#`) or itself (`O`), the game ends.
5. The high score is stored and displayed after the game ends.

## File Details
- `snake_game.cpp` → Contains the main game logic and implementation.
- `highscore.txt` → Stores the highest score achieved in previous games.

## Possible Enhancements
- Implement difficulty levels (adjustable speed or obstacles).
- Add color to the game elements for better visuals.
- Multiplayer mode with two snakes controlled separately.

## Author
Developed by Siddhant, Pearl, Nikhil and Jay.



