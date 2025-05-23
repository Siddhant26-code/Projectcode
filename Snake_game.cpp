#include <iostream>
#include <vector>
#include <conio.h> // For _kbhit() and _getch()
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding random number generator
#include <windows.h> // For Sleep() and SetConsoleCursorPosition()
#include <fstream> // For file operations

using namespace std;

const int BOARD_WIDTH = 70; // Increased width size
const int BOARD_HEIGHT = 20; // Height remains the same
const char EMPTY_CELL = ' ';
const char SNAKE_CELL = 'O';
const char FOOD_CELL = 'X';
const char BORDER_CELL = '#';

enum Direction { UP, DOWN, LEFT, RIGHT };

class Food {
public:
    int x, y;

    void generateFood(const vector<pair<int, int>> &snake) {
        while (true) {
            x = rand() % (BOARD_WIDTH - 2) + 1; // Keep food inside the border
            y = rand() % (BOARD_HEIGHT - 2) + 1;

            // Ensure food does not spawn on the snake
            bool onSnake = false;
            for (const auto &segment : snake) {
                if (segment.first == x && segment.second == y) {
                    onSnake = true;
                    break;
                }
            }

            if (!onSnake) break;
        }
    }
};

class Snake {
public:
    vector<pair<int, int>> body;
    Direction direction;

    Snake() {
        // Initialize snake at a proper position inside the border
        int startX = BOARD_WIDTH / 2, startY = BOARD_HEIGHT / 2;
        body.push_back({startX, startY});
        body.push_back({startX - 1, startY});
        body.push_back({startX - 2, startY});
        direction = RIGHT;
    }

    void move(bool grow = false) {
        // Calculate new head position
        pair<int, int> head = body.front();
        switch (direction) {
            case UP: head.second--; break;
            case DOWN: head.second++; break;
            case LEFT: head.first--; break;
            case RIGHT: head.first++; break;
        }

        // Add new head position
        body.insert(body.begin(), head);

        // If not growing, remove the tail
        if (!grow) body.pop_back();
    }

    bool checkCollision() {
        // Check collision with walls
        pair<int, int> head = body.front();
        if (head.first <= 0 || head.first >= BOARD_WIDTH - 1 || 
            head.second <= 0 || head.second >= BOARD_HEIGHT - 1) {
            return true;
        }

        // Check self-collision
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i] == head) {
                return true;
            }
        }

        return false;
    }
};

class Game {
private:
    Snake snake;
    Food food;
    int score;
    int highScore;
    HANDLE console;
    COORD cursorPosition;
    bool paused;
    vector<vector<char>> buffer;

    void render() {
        // Clear buffer
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                buffer[i][j] = EMPTY_CELL;
            }
        }

        // Render borders
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            buffer[i][0] = BORDER_CELL;
            buffer[i][BOARD_WIDTH - 1] = BORDER_CELL;
        }
        for (int j = 0; j < BOARD_WIDTH; j++) {
            buffer[0][j] = BORDER_CELL;
            buffer[BOARD_HEIGHT - 1][j] = BORDER_CELL;
        }

        // Render snake
        for (const auto &segment : snake.body) {
            buffer[segment.second][segment.first] = SNAKE_CELL;
        }

        // Render food
        buffer[food.y][food.x] = FOOD_CELL;

        // Move cursor to the top-left corner
        SetConsoleCursorPosition(console, {0, 0});

        // Print the buffer to the console in one go
        string screen;
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                screen += buffer[i][j];
            }
            screen += '\n';
        }
        cout << screen;

        // Display score
        cout << "Score: " << score << "  High Score: " << highScore << endl;
    }

    void handleInput() {
        if (_kbhit()) {
            char input = _getch();
            if (input == 0 || input == -32) { 
                input = _getch(); 
                switch (input) {
                    case 72: if (snake.direction != DOWN) snake.direction = UP; break;
                    case 80: if (snake.direction != UP) snake.direction = DOWN; break;
                    case 75: if (snake.direction != RIGHT) snake.direction = LEFT; break;
                    case 77: if (snake.direction != LEFT) snake.direction = RIGHT; break;
                }
            } else {
                switch (input) {
                    case 'w': if (snake.direction != DOWN) snake.direction = UP; break;
                    case 's': if (snake.direction != UP) snake.direction = DOWN; break;
                    case 'a': if (snake.direction != RIGHT) snake.direction = LEFT; break;
                    case 'd': if (snake.direction != LEFT) snake.direction = RIGHT; break;
                    case 'p': paused = !paused; break;
                }
            }
        }
    }

    void loadHighScore() {
        ifstream file("highscore.txt");
        if (file.is_open()) {
            file >> highScore;
            file.close();
        } else {
            highScore = 0;
        }
    }

    void saveHighScore() {
        if (score > highScore) {
            ofstream file("highscore.txt");
            if (file.is_open()) {
                file << score;
                file.close();
            }
        }
    }

public:
    Game() : score(0), paused(false) {
        srand(time(0));
        food.generateFood(snake.body);
        console = GetStdHandle(STD_OUTPUT_HANDLE);
        cursorPosition = {0, 0};
        loadHighScore();
        buffer.resize(BOARD_HEIGHT, vector<char>(BOARD_WIDTH, EMPTY_CELL));

        // Hide cursor
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(console, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(console, &cursorInfo);
    }

    void play() {
        while (true) {
            if (!paused) {
                render();
                handleInput();
                snake.move();

                if (snake.checkCollision()) {
                    cout << "Game Over! Final Score: " << score << endl;
                    saveHighScore();
                    break;
                }

                if (snake.body.front().first == food.x && snake.body.front().second == food.y) {
                    score++;
                    snake.move(true);
                    food.generateFood(snake.body);
                }

                Sleep(75);
            } else {
                handleInput();
                Sleep(75);
            }
        }
    }
};

int main() {
    cout << "Welcome to the Snake Game!" << endl;
    cout << "Controls: W/^ (Up), A/< (Left), S/v (Down), D/> (Right), P (Pause)" << endl;
    cout << "Press any key to start..." << endl;
    _getch();

    Game game;
    game.play();

    return 0;
}
