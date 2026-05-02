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
    Game(Board& board);
    void Draw();
    void Update();
    void ChangeSnakeDirection(Direction direction);
    void CheckCollisionWithFood();
  private:
    Snake snake;
    Food food;
};