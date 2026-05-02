#include "BodyPart.h"

BodyPart::BodyPart(Vector2 pos)
  : pos(pos){}

void BodyPart::Draw(float size, Color color)
{
  Rectangle segment = {
    (float)pos.x * size,
    (float)pos.y * size,
    size, size
  };

  DrawRectangleRounded(
    segment,
    0.5f,
    10,
    color
  );
}

void BodyPart::UpdatePos(Vector2 direction)
{
  pos = Vector2Add(pos, direction);
}

Vector2 BodyPart::GetPos() { return pos; }