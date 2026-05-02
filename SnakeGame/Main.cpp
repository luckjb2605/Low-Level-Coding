#include <raylib.h>
#include <deque>

#include "TextureManager/TextureManager.h"
#include "Board/Board.h"
#include "Game/Game.h"

const int cellCount = 25;
const float cellSize = 30;
const int windowSize = cellCount * cellSize;

const Color green = {139, 195, 74, 255};
const Color darkGreen = {76, 175, 80, 255};

double lastUpdateTime = 0;
bool intervalPassed(double interval)
{
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval)
  {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

int main(void)
{
  InitWindow(windowSize, windowSize, "Retro Snake");
  SetTargetFPS(60);

  Board board = Board(cellCount, cellSize);

  TextureManager::Load(
    TextureName::Apple, 
    "assets/apple.png"
  );

  Game game = Game(board);

  while(!WindowShouldClose())
  {
    BeginDrawing();
      
      board.Draw(green, darkGreen);
      game.Draw();
      
      if (intervalPassed(0.2))
        game.Update();

      if (IsKeyPressed(KEY_W))
        game.ChangeSnakeDirection(Direction::UP);
      if (IsKeyPressed(KEY_A))
        game.ChangeSnakeDirection(Direction::LEFT);
      if (IsKeyPressed(KEY_S))
        game.ChangeSnakeDirection(Direction::DOWN);
      if (IsKeyPressed(KEY_D))
        game.ChangeSnakeDirection(Direction::RIGHT);

      game.CheckCollisionWithFood();
        
    EndDrawing();
  }

  TextureManager::UnloadAll();
  CloseWindow();
  return 0;
}