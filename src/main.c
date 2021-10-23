#include "game.h"

void MainLoop(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello World!", 20, 20, 20, LIGHTGRAY);
    EndDrawing();
}

int main() {
    InitWindow(800, 500, "Raylib Template");

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(MainLoop, 0, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose())
        MainLoop();
#endif

    CloseWindow();
    return (0);
}
