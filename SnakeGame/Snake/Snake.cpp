#include "Snake.h"

Snake::Snake(Board& board, std::deque<Vector2> temp)
  : board(board)
{
  for (const auto& pos : temp)
  {
    body.push_back(BodyPart(pos));
  }
}

void Snake::SetDirection(Direction newDir)
{
  if (
    direction == Direction::UP && newDir == Direction::DOWN ||
    direction == Direction::DOWN && newDir == Direction::UP ||
    direction == Direction::LEFT && newDir == Direction::RIGHT ||
    direction == Direction::RIGHT && newDir == Direction::LEFT
  ) {
    return;
  }
  
  direction = newDir;
}

Vector2 Snake::DirectionToVector()
{
  switch(direction)
  {
    case Direction::UP:    return {0, -1};
    case Direction::DOWN:   return {0, 1};
    case Direction::LEFT:  return {-1, 0};
    case Direction::RIGHT:  return {1, 0};
  }

  return {0, 0};
}

Direction Snake::GetDirection()
{
  return direction;
}

void Snake::Draw(Color color)
{
  for (auto& part : body)
  {
    part.Draw(board.cellSize, color);
  }
}

void Snake::Update()
{
  BodyPart newHead = body[0];
  newHead.UpdatePos(DirectionToVector());
  body.push_front(newHead);
  body.pop_back();
}

bool Snake::IsHeadAt(Vector2 pos)
{
  return Vector2Equals(body[0].GetPos(), pos);
}