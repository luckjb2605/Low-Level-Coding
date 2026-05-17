#include <raylib.h>
#include "constants.h"

typedef struct FireTruck
{
  int x, y;
  Texture2D sprite;
} FireTruck;

int main(void)
{
  InitWindow(WIDTH, HEIGHT, "Doppler Effect");
  SetTargetFPS(60);

  Texture2D firetruckTexture = LoadTexture("assets/firetruck.png");

  FireTruck truck = {0,0,firetruckTexture};

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(BLACK);
      DrawText("Hello", 0,0,40,WHITE);
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}