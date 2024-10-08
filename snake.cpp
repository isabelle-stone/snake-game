#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

static bool allowMove = false;
Color green = {173, 204, 96, 255};
Color brat = {135, 206, 0, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;  // boarder

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque[i], element)) {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;

}

class Snake {
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Draw() {
        for(unsigned int i = 0; i < body.size(); i++) {
            float x = static_cast<float>(body[i].x);
            float y = static_cast<float>(body[i].y);
            Rectangle segment = Rectangle{offset + x * static_cast<float>(cellSize), offset + y * static_cast<float>(cellSize), static_cast<float>(cellSize), static_cast<float>(cellSize)};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update() { 
        if (addSegment == true) {
            body.push_front(Vector2Add(body[0], direction));
            addSegment = false;
        }
        else { /* Removing last segment of snake and adding it to front */
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
        }
    }
    void Restart() {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody) {
        Image image = LoadImage("food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food() {  /* Deconstructor */
        UnloadTexture(texture);
    }

   void Draw() {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody) {
        Vector2 position = GenerateRandomCell();

        while(ElementInDeque(position, snakeBody)) {
            position = GenerateRandomCell();
        }
        return position;
    }
};


class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true; 

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update(){
        if (running) {
            snake.Update();
            EatFood();
            CheckInBounds();
            CheckTailCollision();
        }
        
    }

    void EatFood() { 
        // checking if snake collides with food
        if(Vector2Equals(snake.body[0], food.position)) {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
        }
    }

    void CheckInBounds() {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1) { /* if snake is out of bounds*/
            GameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
            GameOver();
        }
    }

    void GameOver() {
        snake.Restart(); 
        food.position = food.GenerateRandomPos(snake.body);
        running = false;  // pause game
    }

    void CheckTailCollision() {
        deque<Vector2> tail = snake.body;
        tail.pop_front();
        if (ElementInDeque(snake.body[0], tail)) {
            GameOver(); 
        }
    }

};


int main() {
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "SNAKE");
    SetTargetFPS(60);

    Game game = Game();

    // Main game loop:
    while (WindowShouldClose() == false) {
        BeginDrawing();

        if(eventTriggered(0.2)) { /* if interval has passed... */
            game.Update();
        }
        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
            game.running = true;
        }
        if(IsKeyPressed(KEY_DOWN)&& game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
            game.running = true;
        }
        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1){
            game.snake.direction = {-1, 0};
            game.running = true;
        }
        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = {1, 0};
            game.running = true;
        }

        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}