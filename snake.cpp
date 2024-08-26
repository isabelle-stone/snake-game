#include <iostream>
#include <raylib.h>

using namespace std;

static bool allowMove = false;
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

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

    // Main game loop:
    while (WindowShouldClose() == false) {
        BeginDrawing();

        ClearBackground(green);

        food.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}