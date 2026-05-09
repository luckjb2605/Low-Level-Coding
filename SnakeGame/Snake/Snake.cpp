#include "Snake.h"

Snake::Snake(Board& board)
  : board(board),justAte(false){Reset();}
Snake::Snake(Board& board, std::deque<Vector2> temp)
  : board(board), justAte(false)
{
  for (const auto& pos : temp)
  {
    body.push_back(BodyPart(pos));
  }
}

void Snake::SetDirection(Direction newDir)
{
  if (
    direction == Direction::UP    && newDir == Direction::DOWN ||
    direction == Direction::DOWN    && newDir == Direction::UP ||
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
    part.Draw(board.cellSize, board.offset, color);
  }
}

void Snake::Update()
{
  BodyPart newHead = body[0];
  newHead.UpdatePos(DirectionToVector());
  body.push_front(newHead);
  if (!justAte)
  {
    body.pop_back();
    return;
  }
  justAte = false;
}

bool Snake::IsHeadAt(Vector2 pos)
{
  return Vector2Equals(body[0].GetPos(), pos);
}

Vector2 Snake::Head()
{
  return body[0].GetPos();
}

void Snake::Eat()
{
  justAte = true;
}

void Snake::Reset()
{
  direction = Direction::RIGHT;
  body.clear();
  int length = board.cellCount / 3;
  for (int i = length; i > 0; i--)
  {
    body.push_back({{(float)i, 1.0f}});
  }
}

bool Snake::HasInsideDeque(
  const std::deque<BodyPart>& deque,
  Vector2 pos
) {
  for (auto part : deque)
  {
    if (Vector2Equals(part.GetPos(), pos))
    return true;
  }
  return false;
}
bool Snake::HasInsideBody(Vector2 pos)
{ return HasInsideDeque(body, pos); }
bool Snake::HeadInsideBody()
{
  std::deque<BodyPart> headlessBody = body;
  headlessBody.pop_front();
  return HasInsideDeque(headlessBody, Head());
}