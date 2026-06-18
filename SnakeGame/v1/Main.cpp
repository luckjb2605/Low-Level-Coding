#include <raylib.h>
#include <vector>

#include "TextureManager.h"
#include "objects/Snake/Snake.h"
#include "objects/Food/Food.h"
#include "objects/Board/Board.h"

const Color green = {139, 195, 74, 255};
const Color darkGreen = {76, 175, 80, 255};

const float cellSize = 50;
const int cellCount = 15;
const float windowSize = cellSize * cellCount;

int main(void)
{
  InitWindow(windowSize, windowSize, "Retro Snake");
  SetTargetFPS(60);

  Board board = Board(cellCount, cellSize);
  TextureManager::Load(TextureName::Apple, "SnakeGame/assets/apple.png");

  TextureManager::Load(TextureName::SnakeBody, "SnakeGame/assets/snake-atlas-1.png");
  Snake snake((Vector2){0,0}, 4, TextureManager::Get(TextureName::SnakeBody));
  Food rngApple(board.Size(), TextureManager::Get(TextureName::Apple));

  while(!WindowShouldClose())
  {
    BeginDrawing();
    
      board.Draw(green, darkGreen);
      rngApple.Draw(board.CellSize());
      snake.Draw(board.CellSize());

    EndDrawing();
  }

  TextureManager::UnloadAll();
  CloseWindow();
  return 0;
}