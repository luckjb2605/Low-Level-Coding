#include "raylib.h"

int main()
{
  float posX = 0;
  float windowWidth = 800;
  float windowHeight = 450;
  float rectangleWidth = 100;

  InitWindow(windowWidth, windowHeight, "basic window");

  while (!WindowShouldClose())
  {
    if (posX >= (windowWidth - rectangleWidth))
    {
      posX = 0;
    }

    posX += GetFrameTime() * 200;
    
    BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawRectangle(posX, 100, rectangleWidth, 100, BLUE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}