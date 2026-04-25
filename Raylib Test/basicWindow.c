// Ctrl + Shift + P -> C/C++ / Select a Configuration -> MinGW64

#include "raylib.h"

int main()
{
  InitWindow(800, 600, "Hello");

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText("Hello Raylib!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

// MINGW64 TERMINAL:
// gcc Raylib\ Test/main.c -o main -lraylib -lopengl32 -lgdi32 -lwinmm