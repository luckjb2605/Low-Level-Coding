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
    Snake(Board& board);
    void SetDirection(Direction newDir);
    Direction GetDirection();
    Vector2 Head();
    void Draw(Color color);
    void Update();
    bool IsHeadAt(Vector2 pos);
    void Eat();
    void Reset();
    bool HasInsideBody(Vector2 pos);
    bool HeadInsideBody();
  private:
    bool justAte;
    Board& board;
    std::deque<BodyPart> body;
    Direction direction;
    Vector2 DirectionToVector();
    bool HasInsideDeque(
      const std::deque<BodyPart>& deq, 
      Vector2 pos
    );
};