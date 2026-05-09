#include "BodyPart.h"

BodyPart::BodyPart(Vector2 pos)
    : pos(pos) {}

void BodyPart::Draw(float size, float offset, Color color)
{
  Rectangle segment = {
      (float)pos.x * size + offset,
      (float)pos.y * size + offset,
      size, size};

  DrawRectangleRounded(
      segment,
      0.5f,
      10,
      color);
}

Vector2 BodyPart::GetPos() { return pos; }
void BodyPart::UpdatePos(Vector2 direction)
{
  pos = Vector2Add(pos, direction);
}