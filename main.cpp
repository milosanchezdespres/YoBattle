#include "raylib.h"

int main() {
    InitWindow(800, 600, "YoBattle");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Welcome to YoBattle!", 220, 280, 30, RAYWHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}