#include <iostream>
#include <raylib.h>
#include <vector>

#include "objects/Food.h"
#include "TextureManager.h"

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

const float cellSize = 50;
const int cellCount = 15;
const float windowSize = cellSize * cellCount;

int main(void)
{
  std::cout<<"Starting the game...\n";

  InitWindow(windowSize, windowSize, "Retro Snake");
  SetTargetFPS(60);

  TextureManager::Load("apple", "assets/apple.png");

  std::vector<std::vector<Food>> foodArray(cellCount, std::vector<Food>(cellCount));

  for (int i = 0; i < cellCount; i++)
  {
    for (int j = 0; j < cellCount; j++)
    {
      Food food ({i, j}, TextureManager::Get("apple"));
      foodArray[i][j] = food;
    }
  }
  
  while(!WindowShouldClose())
  {
    BeginDrawing();
    
      ClearBackground(green);

      for (const auto& row : foodArray)
      {
        for (const auto& food : row)
        {
          food.Draw(cellSize);
        }
      }
    
    EndDrawing();
  }

  TextureManager::UnloadAll();
  CloseWindow();
  return 0;
}