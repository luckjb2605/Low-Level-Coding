#pragma once

#include <raylib.h>
#include <deque>

#include "BodyPart.h"

class Snake
{
  public:
    Snake(Vector2 pos, int size, Texture2D atlas);
    void Draw(float size);
  private:
    std::deque<BodyPart> body;
};