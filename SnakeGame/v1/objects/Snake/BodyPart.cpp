#include "BodyPart.h"

BodyPart::BodyPart(Texture2D sprite, Vector2 pos)
  : sprite(sprite), pos(pos), xSpeed(1), ySpeed(0){}

void BodyPart::Draw(float size)
{
  DrawRectangle(
    pos.x,
    pos.y,
    size,
    size,
    PURPLE
  );
}