#pragma once
#include <raylib.h>
#include <iostream>

#include "TextureManager/TextureManager.h"
#include "Board/Board.h"

#include "Food/Food.h"
#include "Snake/Snake.h"

const Color snakeGreen = {43, 51, 24, 255};

class Game
{
public:
  Game(Board& board, Music music);
  void Draw();
  void Play();
  void Update();
  int GetScore();
  bool Started();
  bool IsRunning();
  void SwitchPause();
  void ChangeSnakeDirection(Direction direction);
  void CheckCollisionWithFood();
  void CheckCollisionWithBorder();
  void CheckCollisionWithBody();

private:
  Board& board;
  Snake snake;
  Food food;
  bool running;
  int score = 0;
  void GameOver();
  Vector2 GetFoodPosition();
  Sound eat;
  Music music;
  bool started;
};