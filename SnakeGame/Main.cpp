#include <raylib.h>
#include <deque>

#include "TextureManager/TextureManager.h"
#include "Board/Board.h"
#include "Game/Game.h"

const int cellCount = 20;
const float cellSize = 30;
const float offset = cellSize * 2;
const int windowSize =
  cellCount * cellSize + 2 * offset;
const int frameThickness = cellSize / 4;

const Color green = {139, 195, 74, 255};
const Color darkGreen = {76, 175, 80, 255};

const float titleSize = offset * 2 / 3;
const float textSize = windowSize / 20;
const float scoreSize = offset * 1 / 2;

const double frame_duration = 0.1;
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
  InitAudioDevice();
  SetTargetFPS(60);

  Music music = LoadMusicStream("assets/pvz_ost.mp3");
  
  Board board = Board(cellCount, cellSize, offset);
  
  TextureManager::Load(
    TextureName::Apple, 
    "assets/apple.png"
  );
  
  Game game = Game(board, music);

  while(!WindowShouldClose())
  {
    UpdateMusicStream(music);
    BeginDrawing();
    
    board.Draw(green, darkGreen);
    board.DrawFrame(frameThickness, snakeGreen);
    board.DrawTitle(titleSize, snakeGreen);
    board.DrawScore(scoreSize, snakeGreen, 
    game.GetScore(), game.GetHighscore(),
    frameThickness);
    game.Draw();
    
    if (IsKeyPressed(KEY_SPACE)
    || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      if (!game.Started())
      {
        PlayMusicStream(music);
        game.Play();
      }
      game.SwitchPause();
    }
    
    if (game.IsRunning())
    {
      if (intervalPassed(frame_duration))
      {
        game.Update();
        game.CheckCollisionWithFood();
        // game.CheckCollisionWithBorder();
        // game.CheckCollisionWithBody();
      }
      
      if (IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP))
      game.ChangeSnakeDirection(Direction::UP);
      if (IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT))
      game.ChangeSnakeDirection(Direction::LEFT);
      if (IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN))
      game.ChangeSnakeDirection(Direction::DOWN);
      if (IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT))
      game.ChangeSnakeDirection(Direction::RIGHT);
      
      if (IsKeyPressed(KEY_M))
      {
        StopMusicStream(music);
        PlayMusicStream(music);
      }
    } else {
      board.DrawPauseScreen(textSize, snakeGreen);
    }
    
    EndDrawing();
  }
  
  TextureManager::UnloadAll();
  StopMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}