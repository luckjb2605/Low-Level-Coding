#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Board/Board.h"

enum class SegmentType { Head, Body, Tail };

class BodyPart
{
  public:
    BodyPart(Vector2 pos);
    void Draw(float size, Color color);
    void UpdatePos(Vector2 direction);
    Vector2 GetPos();
  private:
    SegmentType type;
    Vector2 pos;
};