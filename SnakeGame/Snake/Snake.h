#pragma once

#include <raylib.h>
#include <deque>

#include "BodyPart.h"
#include "Board/Board.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake
{
  public:
    Snake(Board& board, std::deque<Vector2> temp);
    void SetDirection(Direction newDir);
    Direction GetDirection();
    void Draw(Color color);
    void Update();
    bool IsHeadAt(Vector2 pos);
  private:
    Board& board;
    std::deque<BodyPart> body;
    Direction direction = Direction::RIGHT;
    Vector2 DirectionToVector();
};