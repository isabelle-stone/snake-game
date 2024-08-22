#include <iostream>
#include <raylib.h>

using namespace std;


int main() {
    InitWindow(750, 750, "Snake");
    SetTargetFPS(60);

    // Main game loop
    while (WindowShouldClose() == false){
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();



    return 0;
}