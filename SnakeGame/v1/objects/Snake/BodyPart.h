#pragma once

#include <raylib.h>

class BodyPart
{
  public:
    BodyPart(Texture2D sprite, Vector2 pos);
    void Draw(float size);
  private:
    Texture2D sprite;
    Vector2 pos;
    int xSpeed;
    int ySpeed;
};