#include "Snake.h"

Snake::Snake(Vector2 pos, int size, Texture2D atlas)
{
  for (int x = pos.x; x <= pos.x + size; x++)
  {
    body.push_back(BodyPart(atlas, Vector2{(float)x, pos.y}));
  }
}

void Snake::Draw(float size)
{
  for (BodyPart part : body)
  {
    part.Draw(size);
  }
}