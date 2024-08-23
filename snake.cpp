#include <iostream>
#include <raylib.h>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};


int main() {
    InitWindow(750, 750, "Snake");
    SetTargetFPS(60);

    // Main game loop
    while (WindowShouldClose() == false){
        BeginDrawing();

        ClearBackground(green);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}