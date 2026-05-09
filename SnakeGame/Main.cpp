#include <raylib.h>
#include <deque>

#include "TextureManager/TextureManager.h"
#include "Board/Board.h"
#include "Game/Game.h"

const int cellCount = 15;
const float cellSize = 25;
const float offset = cellSize * 2;
const int windowSize =
  cellCount * cellSize + 2 * offset;
const int frameThickness = cellSize / 4;

const Color green = {139, 195, 74, 255};
const Color darkGreen = {76, 175, 80, 255};

const float titleSize = offset * 2 / 3;
const float textSize = windowSize / 20;
const float scoreSize = offset * 1 / 2;

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

  Board board = Board(cellCount, cellSize, offset);

  TextureManager::Load(
    TextureName::Apple, 
    "assets/apple.png"
  );

  Game game = Game(board);

  while(!WindowShouldClose())
  {
    BeginDrawing();
      
      board.Draw(green, darkGreen);
      board.DrawFrame(frameThickness, snakeGreen);
      board.DrawTitle(titleSize, snakeGreen);
      board.DrawScore(scoreSize, snakeGreen, 
        game.GetScore(), frameThickness);
      game.Draw();

      if (IsKeyPressed(KEY_SPACE))
        game.SwitchPause();
      
      if (game.IsRunning())
      {
        if (intervalPassed(0.2))
        {
          game.Update();
          game.CheckCollisionWithFood();
          game.CheckCollisionWithBorder();
          game.CheckCollisionWithBody();
        }
        
        if (IsKeyPressed(KEY_W))
        game.ChangeSnakeDirection(Direction::UP);
        if (IsKeyPressed(KEY_A))
        game.ChangeSnakeDirection(Direction::LEFT);
        if (IsKeyPressed(KEY_S))
        game.ChangeSnakeDirection(Direction::DOWN);
        if (IsKeyPressed(KEY_D))
        game.ChangeSnakeDirection(Direction::RIGHT);
      } else {
        board.DrawPauseScreen(textSize, snakeGreen);
      }
      
    EndDrawing();
  }

  TextureManager::UnloadAll();
  CloseWindow();
  return 0;
}