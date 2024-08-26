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
int offset = 75;

double lastUpdateTime = 0;


class Snake {
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    void Draw() {
        for(unsigned int i = 0; i < body.size(); i++) {
            float x = static_cast<float>(body[i].x);
            float y = static_cast<float>(body[i].y);
            Rectangle segment = Rectangle{x * static_cast<float>(cellSize), y * static_cast<float>(cellSize), static_cast<float>(cellSize), static_cast<float>(cellSize)};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update() {
        // Removing last segment of snake and adding it to front
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));

    }

};


class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food() {
        Image image = LoadImage("food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    // Deconstructor:
    ~Food() {
        UnloadTexture(texture);
    }


   void Draw() {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomPos() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

};


int main() {
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake Game");
    SetTargetFPS(60);

    Food food = Food();
    Snake snake = Snake();

    // Main game loop:
    while (WindowShouldClose() == false) {
        BeginDrawing();
        snake.Update();

        ClearBackground(green);

        food.Draw();
        snake.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}